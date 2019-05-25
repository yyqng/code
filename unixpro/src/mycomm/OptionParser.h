#pragma once

#include <climits>

#include <boost/container/map.hpp>

#include "comm.h"
#include "MempoolContainers.h"

/**
 * @brief 字符串转换器模板
 * @tparam Type 转换的目标类型
 */
template <typename Type>
struct StringConverter{ };

/**
 * @brief 字符串转换串long类型特例化
 */
template<>
struct StringConverter<long>
{
    bool operator()(const std::string & str, long & out) const
    {
        auto * beg = str.c_str();
        char *end;
        auto const ret = strtol(beg, &end, 0);
        return (*beg != 0 && *end == 0) ? (out = ret), true : false;
    }
};

/**
* @brief 字符串转换串unsigned long类型特例化
*/
template <>
struct StringConverter<unsigned long>
{
    bool operator()(const std::string & str, unsigned long & out) const
    {
        auto i = 0L;

        if (!StringConverter<long>()(str, i))
        {
            return false;
        }

        out = static_cast<unsigned long>(i);
        return true;
    }
};

/**
 * @brief 字符串转换串int类型特例化
 */
template <>
struct StringConverter<int>
{
    bool operator()(const std::string & str, int & out) const
    {
        auto i = 0L;

        if (!StringConverter<long>()(str, i))
        {
            return false;
        }

        if (i < INT_MIN || i > INT_MAX)
        {
            return false;
        }

        out = static_cast<int>(i);
        return true;
    }
};

/**
* @brief 字符串转换串unsigned int类型特例化
*/
template <>
struct StringConverter<unsigned int>
{
    bool operator()(const std::string & str, unsigned int & out) const
    {
        auto i = 0L;

        if (!StringConverter<long>()(str, i))
        {
            return false;
        }

        if (static_cast<unsigned long>(i) > UINT_MAX)
        {
            return false;
        }

        out = static_cast<unsigned int>(i);
        return true;
    }
};

/**
 * @brief 字符串转换串unsigned short类型特例化
 */
template<>
struct StringConverter<unsigned short>
{
    bool operator()(const std::string & str, unsigned short & out) const
    {
        auto i = 0L;

        if (!StringConverter<long>()(str, i))
        {
            return false;
        }

        if (static_cast<unsigned long>(i) > USHRT_MAX)
        {
            return false;
        }

        out = static_cast<unsigned short>(i);
        return true;
    }
};

/**
 * @brief 字符串转换串char类型特例化
 */
template<>
struct StringConverter<char>
{
    bool operator()(const std::string & str, char & out) const
    {
        return str.empty() ? false : ((out = str[0]), true);
    }
};

/**
 * @brief 字符串转换串unsigned char类型特例化
 */
template<>
struct StringConverter<unsigned char>
{
    bool operator()(const std::string & str, unsigned char & out) const
    {
        auto i = 0L;

        if (!StringConverter<long>()(str, i))
        {
            return false;
        }

        if (static_cast<unsigned long>(i) > UCHAR_MAX)
        {
            return false;
        }

        out = static_cast<unsigned char>(i);
        return true;
    }
};

/**
 * @brief 字符串转换器bool类型特例化
 */
template<>
struct StringConverter<bool>
{
    bool operator()(const std::string & str, bool & out) const
    {
        auto ret = true;

        if (str == "true" || str == "yes" || str.empty())   // bool类型的选项，如果是空字符串，即是指定了选项，未指定值，认为是true
        {
            out = true;
        }
        else if (str == "false" || str == "no")
        {
            out = false;
        }
        else
        {
            ret = false;
        }

        return ret;
    }
};

/**
 * @brief 字符串std::string类型特例化
 */
template<>
struct StringConverter<std::string>
{
    bool operator()(const std::string & str, std::string & out) const
    {
        out = str;
        return true;
    }
};

/**
 * @brief Option基类，定义接口
 */
class OptionBase
{
public:
    /**
     * @brief 构造函数
     *
     * @param sample      选项使用示例（使用值传递方式以同时支持左右值引用）
     * @param description 选项描述（使用值传递方式以同时支持左右值引用）
     */
    OptionBase(std::string sample, std::string description)
        : m_sample(std::move(sample))
        , m_description(std::move(description))
    {
    }

    virtual ~OptionBase(void) = default;

    /**
     * @brief 获取Sample字符串
     */
    const std::string & Sample(void) const { return m_sample; }

    std::string & Sample(void) { return m_sample; }

    /**
     * @brief 获取Description字符串
     */
    const std::string & Description(void) const { return m_description; }

    std::string & Description(void) { return m_description; }

    /**
     * @brief 字符串转换接口
     * @param str 输入字符串
     * @return 成功返回true，失败返回false
     */
    virtual bool ConvertFromString(const std::string & str) = 0;

private:
    std::string m_sample;       // 使用示例
    std::string m_description;  // 说明
};

/**
 * @brief 选项解析器
 */
class OptionParser
{
    typedef std::string OptionName;

public:

    /**
     * @brief 禁止复制
     */
    OptionParser(const OptionParser &) = delete;

    /**
     * @brief 禁止移动
     */
    OptionParser(OptionParser &&) = delete;

    /**
     * @brief 禁止复制
     */
    OptionParser & operator=(const OptionParser &) = delete;

    /**
     * @brief 禁止移动
     */
    OptionParser & operator=(OptionParser &&) = delete;

    template <typename...Args>
    bool Register(Args&&...args)
    {
        return m_optionMap.emplace(std::forward<Args>(args)...).second;
    }

    static OptionParser & GetInstance(void);

    /**
     * @brief 解析命令行参数，目前只支持“--option=value”
     *
     * @param argc 参数个数
     * @param argv 参数列表
     * 
     * @return 成功返回true，失败返回false
     */
    bool ParseCommandLine(int argc, char **argv);

    bool ParseConfigFile(const char * file);

    /**
     * @brief 打印帮助信息
     */
    void PrintHelpInformation(void) const;

protected:
    /**
     * @brief 默认构造函数
     */
    OptionParser(void) = default;

    /**
     * @brief 默认析构函数
     */
    ~OptionParser(void) = default;

    /**
     * @brief 通过名称查找选项
     *
     * @param opt 选项名称
     *
     * @return 存在对应选项时返回其属性的指针，不存在时返回nullptr
     */
    OptionBase * GetOption(const std::string & opt)
    {
        auto const itr = m_optionMap.find(opt);
        return m_optionMap.end() == itr ? nullptr : itr->second;
    }

    /**
     * @brief 通过名称查找选项
     *
     * @param opt 选项名称
     *
     * @return 存在对应选项时返回其属性的指针，不存在时返回nullptr
     */
    const OptionBase * GetOption(const std::string & opt) const
    {
        auto const itr = m_optionMap.find(opt);
        return m_optionMap.end() == itr ? nullptr : itr->second;
    }

private:
    std::string m_programName;  //当前程序的名称
    boost::container::map<OptionName, OptionBase *> m_optionMap; // 选项属性表
};

/**
 * @brief 选项值模板
 *
 * @param Value 值类型
 *
 * @param Converter 字符串转换器类型，需要重载bool operator(const std::string &, Value &)函数，默认使用StringConverter类
 */
template <typename Value, typename Converter = StringConverter<Value> >
class Option : public OptionBase
{
public:
    /**
     * @brief 如果Value是基础类型（int, bool, long等）则ReturnValueType即Value类型；否则ReturnValueType即const Value & 类型
     */
    typedef typename std::conditional<std::is_fundamental<Value>::value, Value, const Value &>::type ReturnValueType;
    typedef ReturnValueType ParamType;

    /**
     * @brief 构造函数
     *
     * @param name        选项名称
     * @param defVal      默认值
     * @param sample      选项使用示例（使用值传递方式以同时支持左右值引用）
     * @param description 选项描述（使用值传递方式以同时支持左右值引用）
     */
    Option(const char * name, Value const defVal, std::string sample, std::string description)
        : OptionBase(std::move(sample), std::move(description))
        , m_value(std::move(defVal))
    {
        OptionParser::GetInstance().Register(std::string(name), this);
    }

    /**
     * @brief 获取value值
     */
    ReturnValueType Get(void) const { return m_value; }

    /**
     * @brief 设置value值
     */
    void Set(ParamType value) { m_value = value; }

    /**
     * @brief 基类接口实现
     */
    bool ConvertFromString(const std::string & str) override
    {
        Converter conv;
        return conv(str, m_value);
    }

private:
    Value m_value;          // 选项值
};

// help option
extern Option<bool> g_optHelp;
