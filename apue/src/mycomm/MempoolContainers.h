#pragma once

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>
#include <sstream>

#include "MempoolAllocator.h"

/**
 * @brief hz命名空间，重新定义一些常用的STL容器
 */
namespace hz
{

    /**
     * @brief hz::basic_string模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
#if 0
    template <typename _CharT, typename _Traits = std::char_traits<_CharT>,
        typename _Alloc = hz::MempoolAllocator<_CharT> >
    using basic_string = std::basic_string<_CharT, _Traits, _Alloc>;

    /**
     * @brief hz::string模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    typedef basic_string<char> string;

#else
    typedef std::string string;
#endif

    /**
    * @brief hz::map模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
    */
    template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>,
        typename _Alloc = hz::MempoolAllocator<std::pair<const _Key, _Tp> > >
    using map = std::map<_Key, _Tp, _Compare, _Alloc>;

    /**
     * @brief hz::set模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template <typename _Key, typename _Compare = std::less<_Key>,
        typename _Alloc = hz::MempoolAllocator<_Key> >
    using set = std::set<_Key, _Compare, _Alloc>;

    /**
     * @brief hz::unordered_map模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template<typename _Key, typename _Tp,
        typename _Hash = std::hash<_Key>,
        typename _Pred = std::equal_to<_Key>,
        typename _Alloc = hz::MempoolAllocator<std::pair<const _Key, _Tp> > >
    using unordered_map = std::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>;

    /**
     * @brief hz::unordered_set模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template<typename _Value,
        typename _Hash = std::hash<_Value>,
        typename _Pred = std::equal_to<_Value>,
        typename _Alloc = hz::MempoolAllocator<_Value> >
    using unordered_set = std::unordered_set<_Value, _Hash, _Pred, _Alloc>;

    /**
     * @brief hz::list模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template<typename _Tp, typename _Alloc = hz::MempoolAllocator<_Tp> >
    using list = std::list<_Tp, _Alloc>;

    /**
     * @brief hz::vector模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template<typename _Tp, typename _Alloc = hz::MempoolAllocator<_Tp> >
    using vector = std::vector<_Tp, _Alloc>;

    /**
     * @brief hz::deque模板，替换掉默认的std::allocator，使用内存池版本的hz::MempoolAllocator
     */
    template<typename _Tp, typename _Alloc = hz::MempoolAllocator<_Tp> >
    using deque = std::deque<_Tp, _Alloc>;

    /**
    * @brief hz::queue模板，替换掉默认的std::deque，使用内存池版本的hz::deque
    */
    template<typename _Tp, typename _Sequence = deque<_Tp> >
    using queue = std::queue<_Tp, _Sequence>;

    /**
    * @brief hz::stack模板，替换掉默认的std::deque，使用内存池版本的hz::deque
    */
    template<typename _Tp, typename _Sequence = deque<_Tp> >
    using stack = std::stack<_Tp, _Sequence>;

    /**
     * @brief hz::ostringstream模板，替换掉默认的std::ostringstream，使用内存池版本的hz::deque
     */
    template<typename _CharT, typename _Traits = std::char_traits<_CharT>, typename _Alloc = hz::MempoolAllocator<_CharT> >
    using basic_ostringstream = std::basic_ostringstream<_CharT, _Traits, _Alloc>;

    // hz::ostringstream
    typedef basic_ostringstream<char> ostringstream;

    /**
     * @brief hz::istringstream模板，替换掉默认的std::istringstream，使用内存池版本的hz::deque
     */
    template<typename _CharT, typename _Traits = std::char_traits<_CharT>, typename _Alloc = hz::MempoolAllocator<_CharT> >
    using basic_istringstream = std::basic_istringstream<_CharT, _Traits, _Alloc>;

    // hz::istringstream
    typedef basic_istringstream<char> istringstream;

} // namespace hz
