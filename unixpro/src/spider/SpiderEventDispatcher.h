#pragma once

#include "comm.h"
#include "EventDispatcher.h"

namespace spider
{

    class EventDispatcher
        : public ::EventDispatcher
    {
    public:
        /**
         * @brief 构造函数
         */
        EventDispatcher(void)
            : m_statisInterval(std::chrono::seconds(60))
        {
        }

        /**
         * @brief 禁止复制&移动
         */
        EventDispatcher(EventDispatcher &&) = delete;
        EventDispatcher(const EventDispatcher &) = delete;
        EventDispatcher & operator=(const EventDispatcher &) = delete;
        EventDispatcher & operator=(EventDispatcher &&) = delete;

        /**
         * @brief 获取单例对象的引用
         */
        static spider::EventDispatcher & GetInstance(void);

    protected:
        /**
         * @brief 默认析构函数
         */
        ~EventDispatcher(void) = default;

        /**
         * @brief 超时处理函数实现
         *
         * @param now 当前的单调时间
         */
        void OnTimeout(std::chrono::steady_clock::time_point now) override;

        /**
         * @brief 任务派发接口
         * @param listener 事件订阅者，不可为空指针
         * @param events 事件类型
         */
        void OnDispatch(EventListener * listener, uint32_t events) override;

        /**
         * @brief 事件循环调用函数实现
         */
        void OnLoop(void) override;

        /**
         * @brief 打印统计信息
         * @param now 当前单调时间
         */
        void LogStatisticalInformation(std::chrono::steady_clock::time_point now);

    private:
        std::chrono::steady_clock::duration m_statisInterval;   // 打印统计的时间间隔
        std::chrono::steady_clock::time_point m_lastStatis;     // 上次打印统计的时间
    };

}
