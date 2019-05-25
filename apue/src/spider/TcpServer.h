#pragma once

#include <sys/socket.h>

#include <memory>

#include "comm.h"
#include "FileDescriptor.h"
#include "EventListener.h"

class TcpServer
    : public EventListener
{
public:
    /**
     * @brief 默认构造函数
     */
    TcpServer(void) = default;

    /**
     * @brief 构造，并监听指定端口
     * @param port 监听端口
     */
    TcpServer(unsigned short port)
    {
        Listen(port);
    }

    /**
     * @brief 禁止复制
     */
    TcpServer(const TcpServer &) = delete;

    /**
     * @brief 移动构造函数
     */
    TcpServer(TcpServer && other)
        : m_sock(std::move(other.m_sock))
    {
    }

    /**
     * @brief 默认析构函数
     */
    virtual ~TcpServer(void) = default;

    /**
     * @brief 禁止复制
     */
    TcpServer & operator=(const TcpServer &) = delete;

    /**
     * @brief 移动赋值函数
     */
    TcpServer & operator=(TcpServer && other)
    {
        if (this != &other)
        {
            m_sock = std::move(other.m_sock);
        }
        return *this;
    }

    /**
     * @brief 启动监听，默认接收任意目的IP的连接
     * @param port 监听端口
     * @return
     *      true - 成功
     *      false - 失败
     */
    bool Listen(unsigned short port);

    /**
     * @brief 启动监听，UNIX域套接字版本
     * @param path UNIX域套接字路径
     * @return
     *      true - 成功
     *      false - 失败
     */
    bool Listen(const char * path);

    /**
     * @brief 判断服务器是否已启动监听
     * @return
     *      true - 已经启动监听
     *      false - 未启动监听
     */
    operator bool(void) const { return m_sock; }

    /**
     * @brief 判断服务器是否已启动监听
     * @return
     *      true - 未启动监听
     *      false - 已经启动监听
     */
    bool operator!(void) const { return !m_sock; }

    /**
     * @brief 获取套接字值
     */
    int GetFd(void) const override final { return m_sock.Get(); }

protected:
    /**
     * @brief 监听套接字可读时即有新的连接，接受新的连接并调用OnAccept方法，请勿重写
     */
    void OnRead(void) override final;

    /**
     * @brief tcp服务器的监听套接字，不处理写事件
     */
    void OnWrite(void) override final { }

    /**
     * @brief 当
     */
    virtual void OnAccept(FileDescriptor && sock, sockaddr_storage & addr, socklen_t addrlen) = 0;

private:
    FileDescriptor m_sock;  // 服务器监听套接字
    static const char * const s_tag;
};

