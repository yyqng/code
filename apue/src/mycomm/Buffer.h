#pragma once

#include "comm.h"

/**
 * Buffer以4K为最小分配粒度，当请求分配内存的大小会向上对齐到4K边界
 * Buffer类增加内存大小时采用重映射内存的方式，减少内存的拷贝
 */
class Buffer
{
public:
    /**
     * @brief 构造函数
     */
    Buffer(void)
        : m_ptr(nullptr)
        , m_size(0)
    {
    }

    /**
     * @brief 禁止复制
     */
    Buffer(const Buffer &) = delete;

    /**
     * @brief 移动构造
     */
    Buffer(Buffer && other)
        : m_ptr(other.m_ptr)
        , m_size(other.m_size)
    {
        other.m_ptr = nullptr;
        other.m_size = 0;
    }

    /**
     * @brief 析构函数
     */
    ~Buffer(void) { Free(); }

    /**
     * @brief 禁止复制
     */
    Buffer & operator=(const Buffer &) = delete;

    /**
     * @brief 移动赋值
     */
    Buffer & operator=(Buffer && other);

    /**
     * @brief copy-free的重新分配内存
     */
    Buffer & Realloc(size_t size);

    /**
     * @brief 释放内存
     */
    void Free(void);

    /**
     * @brief 获取内存指针
     */
    void * Get(void) const { return m_ptr; }

    /**
     * @brief 判断内存是否有效
     */
    operator bool(void) const { return bool(m_ptr); }

    bool operator!(void) const { return !m_ptr; }

private:
    void * m_ptr;
    size_t m_size;
};
