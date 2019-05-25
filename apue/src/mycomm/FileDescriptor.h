#pragma once

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "comm.h"

/**
 * @brief FileDescriptor封装了文件描述符
 */
class FileDescriptor
{
public:
    /**
     * @brief 构造函数
     * @param fd 文件描述符，默认为-1
     */
    FileDescriptor(int const fd = -1)
        : m_fd(fd)
    {
    }

    /**
     * @brief 复制构造函数，通过fcntl复制文件描述符
     * @param other 被复制的文件描述符对象
     */
    FileDescriptor(const FileDescriptor & other)
        : m_fd(other.m_fd == -1 ? -1 : fcntl(other.m_fd, F_DUPFD, 0))
    {
    }

    /**
     * @brief 移动构造函数
     * @param other 被移动的对象，将被清空
     */
    FileDescriptor(FileDescriptor && other) noexcept
        : m_fd(other.m_fd)
    {
        other.m_fd = -1;
    }

    /**
     * @brief 析构函数
     */
    ~FileDescriptor(void)
    {
        if (m_fd >= 0) ::close(m_fd);
    }

    /**
     * @brief 获取文件描述符的值
     */
    int Get(void) const
    {
        return m_fd;
    }

    /**
     * \brief 重设fd
     */
    void Reset(int const fd)
    {
        if (fd != -1) ::close(m_fd);
        m_fd = fd;
    }

    /**
     * @brief 关闭文件描述符
     */
    void Close(void)
    {
        ::close(m_fd);
        m_fd = -1;
    }

    /**
     * @brief 设置文件描述符为非阻塞
     * @return
     *      true - 成功
     *      false - 失败
     */
    bool SetNonblocking(void) const
    {
        auto const ret = fcntl(m_fd, F_GETFL);
        if (ret == -1)
            return false;
        return fcntl(m_fd, F_SETFL, ret | O_NONBLOCK) != -1;
    }

    /**
     * @brief 重载opertor !
     * @return
     *      true - 文件描述符为无效值
     *      false - 文件描述符为有效值
     */
    bool operator!(void) const
    {
        return m_fd == -1;
    }

    /**
     * @brief 重载bool强制转换
     * @return
     *      true - 文件描述符为有效值
     *      false - 文件描述为无效值
     */
    operator bool() const
    {
        return m_fd != -1;
    }

    /**
     * @brief 复制赋值函数，通过fcntl来复制文件描述符
     * @param other 被复制的文件描述符对象
     */
    FileDescriptor & operator=(const FileDescriptor & other)
    {
        if (this != &other)
            m_fd = other.m_fd == -1 ? -1 : ::fcntl(other.m_fd, F_DUPFD, 0);
        return *this;
    }

    /**
     * @brief 移动赋值函数
     * @param other 被移动的对象
     */
    FileDescriptor & operator=(FileDescriptor && other) noexcept
    {
        if (this != &other)
        {
            m_fd = other.m_fd;
            other.m_fd = -1;
        }
        return *this;
    }

    /**
     * @brief 重载operator<
     */
    bool operator<(const FileDescriptor & other) const
    {
        return m_fd < other.m_fd;
    }

    private:
        int m_fd;
    };

