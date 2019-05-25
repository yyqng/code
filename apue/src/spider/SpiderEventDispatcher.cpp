#include <cstdint>
#include <cassert>

#include "Log.h"
#include "PublicServer.h"
#include "SpiderEventDispatcher.h"
#include "PublicConnectionManager.h"
#include "PrivateConnectionManager.h"
#include "CurlManager.h"
#include "EventListener.h"
#include "ProxyPool.h"
#include "SpiderOptions.h"

namespace spider
{

    static auto & s_connectionMgr = spider::PublicConnectionManager::GetInstance();
    static auto & s_privateConnectionMgr = spider::PrivateConnectionManager::GetInstance();
    static auto & s_curlMgr = spider::CurlManager::GetInstance();
    static auto & s_proxyPool = spider::ProxyPool::GetInstance();

    spider::EventDispatcher & EventDispatcher::GetInstance(void)
    {
        static spider::EventDispatcher s_dispatcher;    // 局部静态变量的初始化从C++11标准开始是线程安全的
        return s_dispatcher;
    }

    void EventDispatcher::LogStatisticalInformation(std::chrono::steady_clock::time_point const now)
    {
        // 将idle与busy时间转化为double类型的毫秒时间
        auto const idle = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000> > >(GetIdle());
        auto const busy = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000> > >(GetBusy());
        auto const total = idle + busy;

        // 计算百分比
        auto const idleCenti = idle.count() / total.count() * 100;
        auto const busyCenti = busy.count() / total.count() * 100;

        // 统计任务数
        size_t nStagedRecv, nStagedFail, nStagedDrop, nStagedFinish;
        std::tie(nStagedRecv, nStagedFail, nStagedDrop, nStagedFinish) = s_curlMgr.GetStagedTaskNumbers();

        // 重置idle, busy, nrecv, nfail, ndrop
        s_curlMgr.CommitStagedTaskNumbers();

        size_t nTotalRecv, nTotalFail, nTotalDrop, nTotalFinish;
        std::tie(nTotalRecv, nTotalFail, nTotalDrop, nTotalFinish) = s_curlMgr.GetTotalTaskNumbers();
        auto const nrunning = s_curlMgr.GetCurrentRunningHandleNumber();

        // 重置cpu统计
        ResetCpuUsageTimers();

        // 统计代理数
        auto const proxyNums = s_proxyPool.GetProxyNumbers();

        // 打印日志
        auto & log = sLog;
        static auto const s_statisTag = "Statis";
        log.Write(Log::INF, s_statisTag, "      CPU USAGE:\tidle=(%.2fms, %.2f%%), busy=(%.2fms, %.2f%%)\n",
                  idle.count(), idleCenti, busy.count(), busyCenti);
        log.Write(Log::INF, s_statisTag, "   TASK NUMBERS:\trecv=(%ld/min, %ld/tot), fail=(%ld/min, %ld/tot), drop=(%ld/min, %ld/tot), finish=(%ld/min, %ld/tot), running=%ld, queuing=%ld\n",
                  nStagedRecv, nTotalRecv, nStagedFail, nTotalFail, nStagedDrop, nTotalDrop, nStagedFinish, nTotalFinish, nrunning, s_curlMgr.GetTaskQueueSize());
        log.Write(Log::INF, s_statisTag, "  PROXY NUMBERS:\trecv=%ld, drop=%ld, available=%ld\n",
                  std::get<0>(proxyNums), std::get<1>(proxyNums), std::get<2>(proxyNums));

        // 打印带宽使用日志
        if (g_optBandwidthMetering.Get())
        {
            size_t nUpload, nDownload;
            std::tie(nUpload, nDownload) = s_curlMgr.GetTransferredBytesNumber();
            s_curlMgr.ResetTransferredBytesNumber();

            auto const totalSec = total.count() / 1000;
            auto upSpeed = (nUpload << 3) / totalSec;
            auto dnSpeed = (nDownload << 3) / totalSec;

            static const char * measurements[] = { "b", "Kb", "Mb", "Gb" };
            size_t upIdx = 0, dnIdx = 0;
            while (upIdx < __countof(measurements) && upSpeed > 1024) { upSpeed /= 1024; ++upIdx; };
            while (dnIdx < __countof(measurements) && dnSpeed > 1024) { dnSpeed /= 1024; ++dnIdx; };

            log.Write(Log::INF, s_statisTag, "BANDWIDTH USAGE:\tup=%.2f%sps, dn=%.2f%sps\n",
                upSpeed, measurements[upIdx], dnSpeed, measurements[dnIdx]);
        }
    }

    void EventDispatcher::OnTimeout(std::chrono::steady_clock::time_point const now)
    {
        // 打印统计
        if (now - m_lastStatis > m_statisInterval)
        {
            LogStatisticalInformation(now);
            m_lastStatis = now;
        }

        // 清理超时不活跃的连接
        s_connectionMgr.CleanupExpired(now);

        // 调用代理池超时函数
        s_proxyPool.OnTimeout(now);
    }

    void EventDispatcher::OnDispatch(EventListener * const listener, uint32_t const events)
    {
        assert(listener);

        // 处理事件
        listener->HandleEvent(events);
    }

    void EventDispatcher::OnLoop(void)
    {
        // 处理listener任务
        s_connectionMgr.HandleListenerTask();
        s_privateConnectionMgr.HandleListenerTask();

        // 清理Curl的失败订阅
        s_curlMgr.Cleanup();

        // 处理Curl的结果
        s_curlMgr.HandleCurlResult();

        // 新创建的easy curl对象在加入到multi curl后，easy curl对象以1ms的超时值挂在multi curl内部的超时表中
        // 通过curl_multi_socket_action传入CURL_SOCKET_TIMEOUT参数来驱动libcurl调用socket_callback
        CheckExprLogAbort(s_curlMgr.MultiSocketAction(CURL_SOCKET_TIMEOUT),
                          Log::ERR, "MultiCurl", "Multi curl socket action on timeout failed\n");
    }
}
