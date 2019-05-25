#pragma once

#include <cstdlib>
#include <cassert>

#include "comm.h"

namespace hz
{

    // TODO: 将来替换成内存池分配函数
    void * (* const MempoolAlloc)(size_t) = malloc;
    void (*const MempoolDealloc)(void *) = free;

    /**
     * @brief 内存池版本的allocator
     * 与STL和BOOST容器兼容的内存池版本allocator
     */
    template <class Type>
    class MempoolAllocator
    {
    public:
        typedef Type value_type;
        typedef value_type * pointer;
        typedef value_type const * const_pointer;
        typedef value_type & reference;
        typedef const value_type & const_reference;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;

        /**
         * @brief 模板参数转换器
         */
        template <class OtherType>
        struct rebind
        {
            typedef MempoolAllocator<OtherType> other;
        };

        /**
         * @brief 默认构造函数
         */
        MempoolAllocator(void) = default;

        /**
         * @brief 默认复制构造函数
         */
        MempoolAllocator(const MempoolAllocator &) = default;

        /**
         * @brief 从MempoolAllocator<OtherType>类型构造
         */
        template <typename OtherType>
        MempoolAllocator(const MempoolAllocator<OtherType> &) { }

        /**
         * @brief 默认析构函数
         */
        ~MempoolAllocator(void) = default;

        /**
         * @brief 默认复制赋值函数
         */
        MempoolAllocator & operator=(const MempoolAllocator &) = default;

        /**
         * @brief 内存分配
         * @param n 分配内存的大小
         * @return 返回分配的内存指针，失败时返回空指针
         */
        pointer allocate(std::size_t const n, const void * = nullptr)
        {
            return static_cast<pointer>(MempoolAlloc(n * sizeof (value_type)));
        }

        /**
         * @brief 内存释放
         * @param p 需要释放的内存指针
         * @param n 需要释放的内存的大小（暂时未使用到）
         */
        void deallocate(const pointer p, std::size_t n)
        {
            MempoolDealloc(p);
        }

        /**
         * @brief 在地址p上构造对象
         * @param p 缓冲区地址，不可为空指针
         * @param args 构造对象的参数列表
         */
        template <typename OtherType, typename... Args>
        void construct(OtherType * p, Args&&... args)
        {
            assert(p);
            ::new (static_cast<void *>(p)) OtherType(std::forward<Args>(args)...);
        }

        /**
         * @brief 在地址p上调用析构函数
         * @param p 将被析构的对象指针，不可为空指针
         */
        template <typename OtherType>
        void destroy(OtherType * p)
        {
            assert(p);
            p->~OtherType();
        }

        /**
         * @brief 获取对象的地址
         * @param x 对象的引用
         */
        pointer address(reference x) const
        {
            return &x;
        }

        /**
         * @brief 获取对象的地址
         * @param x 对象的引用
         */
        const_pointer address(const_reference x) const
        {
            return &x;
        }

        /**
         * @brief ==重载，总是返回true
         */
        template<typename OtherType>
        bool operator==(const MempoolAllocator<OtherType> other) const
        {
            return true;
        }

        /**
         * @brief !=重载，总是返回false
         */
        template<typename OtherType>
        bool operator!=(const MempoolAllocator<OtherType> & other) const
        {
            return false;
        }

        /**
         * @brief 可分配元素的最大数量
         */
        std::size_t max_size(void) const
        {
            return std::size_t(-1) / sizeof (value_type);
        }
    };

}
