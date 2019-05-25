#include <libgen.h> // basename
#include <unistd.h> // daemon

#include <iostream>
#include <iomanip>  // std::setw
#include <cstdlib>  // system

#include "comm.h"
#include "Log.h"
#include "SpiderOptions.h"
#include "OptionParser.h"
#include "SpiderEventDispatcher.h"
//#include "PublicServer.h"
//#include "PrivateServer.h"
//#include "CurlManager.h"
//#include "ShmOutput.h"
//#include "ProxyPool.h"
//#include "Timer.hpp"

inline void InitializeLog(void)
{
	if (!Log::Initialize(g_optLogDir.Get().c_str(), "spider", g_optLogLevelMask.Get()))
    {
        std::cerr << __FUNCTION__ << ": failed to initialize Log" << std::endl;
        exit(EXIT_FAILURE);    // 初始化时的致命错误，直接终止进程
    }
}

void InitializePublicServer(void)
{
   auto const publicServerTag = "PublicServer";
    auto & publicServer = spider::PublicServer::GetInstance();

    // 启动public server；若失败，直接终止进程
    if (!publicServer.Listen(g_optPort.Get()))
    {
        std::cerr << __FUNCTION__ << ": public server failed to listen on " << g_optPort.Get() << std::endl;
        sLog.Write(Log::ERR, "spider", "failed to listen on %d\n", g_optPort.Get());
        exit(EXIT_FAILURE);
    }

    // public server订阅事件；若失败，则直接终止进程
    auto & eventDispatcher = spider::EventDispatcher::GetInstance();

    if (!eventDispatcher.Subscribe(publicServer, EventDispatcher::READ | EventDispatcher::EDGE))
    {
        std::cerr << __FUNCTION__ << ": public server failed to subscribe read event" << g_optPort.Get() << std::endl;
        sLog.Write(Log::ERR, publicServerTag, "failed to subscribe read event\n");
        exit(EXIT_FAILURE);
    }
    sLog.Write(Log::INF, publicServerTag, "Listening on %u\n", g_optPort.Get());
}

void InitializePrivateServer(void)
{
 	/*
    auto const privateServerTag = "PrivateServer";
   auto & privateServer = spider::PrivateServer::GetInstance();

   // 启动private server；若失败，则直接终止进程
    if (!privateServer.Listen(g_optUnixDomainSocketPath.Get().c_str()))
    {
        std::cerr << __FUNCTION__ << ": private server failed to listen on " << g_optUnixDomainSocketPath.Get() << std::endl;
        sLog.Write(Log::ERR, privateServerTag, "failed to listen on %s\n", g_optUnixDomainSocketPath.Get().c_str());
        exit(EXIT_FAILURE);
    }

    // private server订阅事件；若失败，则直接终止进程
    auto & eventDispatcher = spider::EventDispatcher::GetInstance();

    if (!eventDispatcher.Subscribe(privateServer, EventDispatcher::READ | EventDispatcher::EDGE))
    {
        std::cerr << __FUNCTION__ << ": private server failed to subscribe read event" << std::endl;
        sLog.Write(Log::ERR, privateServerTag, "failed to subscribe read event\n");
        exit(EXIT_FAILURE);
    }
    sLog.Write(Log::INF, privateServerTag, "listening on %s\n", g_optUnixDomainSocketPath.Get().c_str());
*/
}

void InitializeShmOutput(void)
{
    auto const shmOutputTag = "ShmOutput";
	printf("shmOutputTag : %s\n", shmOutputTag);
		/*
    if (g_optHasPktspyMgr.Get())
    {
        // 获取输出通道数量；若失败，则直接终止进程
        auto & shmFdList = g_optShmFdList.Get();

        if (shmFdList.size() <= 0)
        {
            std::cerr << __FUNCTION__ << ": pktspymgr is set, but no shm file descriptor list" << std::endl;
            sLog.Write(Log::ERR, shmOutputTag, "pktspymgr is set, but no shm file descriptor list\n");
            exit(EXIT_FAILURE);
        }

        auto & output = spider::ShmOutput::GetInstance();

        for (auto itr = shmFdList.begin(); itr != shmFdList.end(); ++itr)
        {
            // 附着输出通道；若失败，则直接终止进程
            if (!output.AttachOutputChannel(*itr))
            {
                std::cerr << __FUNCTION__ << ": failed to create output channel" << std::endl;
                sLog.Write(Log::ERR, shmOutputTag, "failed to create output channel\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        // 创建输出通道；若失败，则直接终止进程
        if (!spider::ShmOutput::GetInstance().CreateOutputChannel(g_optShmObjName.Get().c_str(), 16 << 20))
        {
            std::cerr << __FUNCTION__ << ": failed to create output channel" << std::endl;
            sLog.Write(Log::ERR, shmOutputTag, "failed to create output channel\n");
            exit(EXIT_FAILURE);
        }
    }
    sLog.Write(Log::INF, shmOutputTag, "shm output initialize success!\n");
*/
}

inline void InitializeMultiCurl(void)
{
	/*
   // 初始化Multi CURL；若失败，则直接终止进程
    if (!spider::CurlManager::GetInstance().Initialize())
    {
        std::cerr << __FUNCTION__ << ": failed to initialize multi curl manager" << std::endl;
        sLog.Write(Log::ERR, "MultiCurl", "failed to initialize\n");
        exit(EXIT_FAILURE);
    }
	*/
}

inline void Daemonlize(void)
{
    // 转变化守护进程；若失败，则直接终止进程
    if (daemon(1, 0) == 0)
    {
        std::cerr << __FUNCTION__ << ": failed to daemonlize" << std::endl;
        exit(EXIT_FAILURE);
    }
}

inline void InitializeProxyPool(void)
{
	/*
    auto & proxyPool = spider::ProxyPool::GetInstance();
    if (!proxyPool.Initialize("data/proxy.data"))
    {
        std::cerr << __FUNCTION__ << ": proxy pool initialization failure" << std::endl;
        sLog.Write(Log::ERR, "ProxyPool", "initialization failure: %m\n");  // TODO: proxy data config
        exit(EXIT_FAILURE);
    }*/
}

int main(int const argc, char **argv)
{
    // 解析命令行
    // 判断是否指定help选项，指定help时忽略其它选项，打印帮助信息并退出
    if (!OptionParser::GetInstance().ParseCommandLine(argc, argv) || g_optHelp.Get())
    {
        OptionParser::GetInstance().PrintHelpInformation();
        return 0;
    }

    if (!g_optConfig.Get().empty())
    {
        // 解析配置文件
        if (!OptionParser::GetInstance().ParseConfigFile(g_optConfig.Get().c_str()))
        {
            OptionParser::GetInstance().PrintHelpInformation();
            return 0;
        }

        // 命令行的优先级更高，再次解析命令行，使命令行覆盖相同配置
        OptionParser::GetInstance().ParseCommandLine(argc, argv);
    }
    // 日志初始化
    InitializeLog();

    // 启动public server
    InitializePublicServer();

    // 启动private server
    InitializePrivateServer();

    // 初始化输出共享内存
    InitializeShmOutput();

    // 初始化Multi-Curl
    InitializeMultiCurl();

    // 初始化代理池
    InitializeProxyPool();

    // 启动事件循环
    //spider::EventDispatcher::GetInstance().Run(256, 1);

    return 0;
}
