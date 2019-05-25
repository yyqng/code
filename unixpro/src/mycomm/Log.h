#pragma once

#include <pthread.h>

#include <cassert>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <array>

#include <openssl/aes.h>

#include "comm.h"
#include "MempoolContainers.h"
#include "Buffer.h"

class Log
{
public:
    /**
     * @brief 标志位结构
     */
    struct FmtFlags
    {
        uint32_t m_base         : 2;    // 进制,OCT,DEC,HEX
        uint32_t m_alignment    : 2;    // 对齐,LEFT,INTERNAL,RIGHT
        uint32_t m_showbase     : 1;    // 是否输出进制前缀
        uint32_t m_showpos      : 1;    // 正数是否输出'+'
        uint32_t m_boolalpha    : 1;    // bool值输出为true,false字符串
        uint32_t m_scientific   : 1;    // 是否使用科学计数
        uint32_t m_precision    : 2;    // 浮点型精度类型
        uint32_t m_level        : 2;    // 日志级别位
        uint32_t m_levelmask    : 4;    // 日志级别掩码
        uint32_t                : 8;    // 保留位
        uint32_t m_fill         : 8;    // 填充字符
    };

protected:

    /**
     * @brief 直接输出方式
     */
    struct DirectPut { };

    /**
     * @brief 进制枚举
     */
    enum BaseBit { OCT = 0, DEC = 1, HEX = 2 };

    /**
     * @brief 对齐方式枚举
     */
    enum AlignmentBit { LEFT = 0, INTERNAL = 1, RIGHT = 2 };

    /**
     * @brief 精度枚举
     */
    enum PrecisionBit { DEFFLOAT = 0, FIXED = 1, PRECISE = 2 };

    /**
     * @brief 宽度控制类型
     */
    struct Width { unsigned int m_n; };

    /**
     * @brief 填充字符类型
     */
    struct Fill { char m_c; };

    /**
     * @brief 精度类型
     */
    struct Precision { int m_n; };

    /**
     * @brief 日期结构
     */
    struct Date { int m_year, m_month, m_day; };

    using initial_vector = std::array<unsigned char, 16>;

public:
    /**
     * @brief 日志级别，增加日志级别时，请同时增加s_levelString中的名称
     */
    enum Level : uint32_t { DBG = 0, INF = 1, WRN = 2, ERR = 3 };

    /**
     * @brief Level对应的字符串
     */
    static const char * const s_levelString[];

    /**
     * @brief 禁止复制
     */
    Log(const Log &) = delete;

    /**
     * @brief 禁止移动
     */
    Log(Log &&) = delete;

    /**
     * @brief 析构函数
     */
    ~Log(void) { Flush(); }

    /**
     * @brief 禁止复制
     */
    Log & operator=(const Log &) = delete;

    /**
     * @brief 禁止移动
     */
    Log & operator=(Log &&) = delete;

    /**
     * @brief 初始化
     *
     * @param workdir          日志文件目录，为空指针/空字符串时，表示启动目录
     * @param initialLevelMask 初始日志级别掩码
     * @param module           模块名，不可为NULL
     *
     * @param key 密钥串，空指针/空字符串表示不加密
     */
    static bool Initialize(const char * workdir, const char * module, uint32_t initialLevelMask = 0x0F, const char * key = nullptr);

    /**
     * @brief 获取与当前线程绑定的Log对象
     */
    static Log & GetInstance(void);

    /**
     * @brief 重载bool转换，判断Log文件是否打开
     */
    operator bool(void) const { return bool(m_ofs); }

    /**
     * @brief 设置Level与用户Tag，调用此函数表示一条新日志纪录的开始，将日志前缀写入日志文件
     *
     * @param level 日志级别
     * @param tag   用户自定义tag，为NULL时使用默认标签，Tag用于日志过滤
     *
     * @return 返回*this对象的引用
     */
    Log & operator()(Level const level, const char * tag = nullptr)
    {
        m_flags.m_level = uint32_t(level);
        if ((1u << uint32_t(level)) & m_flags.m_levelmask)
        {
            if (!tag) tag = "default";
            MakePrefix(level, tag);
        }
        return *this;
    }

    /**
     * @brief 输出一个字符到日志纪录中
     */
    Log & operator<<(char const c)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutChar(c);
        return *this;
    }

    /**
     * @brief 输出一个short整数到日志纪录中
     */
    Log & operator<<(short const s)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask)
        {
            m_flags.m_base == OCT || m_flags.m_base == HEX
                ? PutInteger(static_cast<unsigned long long>(static_cast<unsigned short>(s)))
                : PutInteger(static_cast<long long>(s));
        }
        return *this;
    }

    /**
     * @brief 输出一个int整数到日志纪录中
     */
    Log & operator<<(int const i)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask)
        {
            m_flags.m_base == OCT || m_flags.m_base == HEX
                ? PutInteger(static_cast<unsigned long long>(static_cast<unsigned int>(i)))
                : PutInteger(static_cast<long long>(i));
        }
        return *this;
    }

    /**
     * @brief 输出一个long整数到日志纪录中
     */
    Log & operator<<(long const l)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(static_cast<long long>(l));
        return *this;
    }

    /**
     * @brief 输出一个long整数到日志纪录中
     */
    Log & operator<<(long long const ll)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(ll);
        return *this;
    }

    /**
     * @brief 输出无符号char，强制转换成signed char输出
     */
    Log & operator<<(unsigned char const uc)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutChar(uc);
        return *this;
    }

    /**
     * @brief 输出无符号short到日志纪录中
     */
    Log & operator<<(unsigned short const us)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(static_cast<unsigned long long>(us));
        return *this;
    }

    /**
     * @brief 输出无符号int到日志纪录中
     */
    Log & operator<<(unsigned int const ui)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(static_cast<unsigned long long>(ui));
        return *this;
    }

    /**
     * @brief 输出无符号long到日志纪录中
     */
    Log & operator<<(unsigned long const ul)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(static_cast<unsigned long long>(ul));
        return *this;
    }

    /**
     * @brief 输出无符号long long到日志纪录中
     */
    Log & operator<<(unsigned long long const ull)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutInteger(ull);
        return *this;
    }

    /**
     * @brief 输出float串到日志纪录中
     */
    Log & operator<<(float const f)
    {
        // TODO:
        return *this;
    }

    /**
     * @brief 输出double串到日志纪录中
     */
    Log & operator<<(double const d)
    {
        // TODO:
        return *this;
    }

    /**
     * @brief 输出long double串到日志纪录中
     */
    Log & operator<<(long double const ld)
    {
        // TODO:
        return *this;
    }

    /**
     * @brief 输出字符串到日志纪录中
     */
    Log & operator<<(const char * str)
    {
        assert(str);
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) PutStr(str, strlen(str));
        return *this;
    }

    /**
     * @brief 输出字符串到日志纪录中，返回*this对象的引用
     */
    Log & operator<<(const std::string & str)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask)
        {
            if (!str.empty())
            {
                PutStr(str.c_str(), str.length());
            }
        }
        return *this;
    }

#if 0
    /**
     * @brief 输出字符串到日志纪录中，返回*this对象的引用
     */
    Log & operator<<(const hz::string & str)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask)
        {
            if (!str.empty())
            {
                PutStr(str.c_str(), str.length());
            }
        }
        return *this;
    }
#endif

    /**
     * @brief 控制下一个输出的宽度，返回*this对象的引用
     */
    Log & operator<<(Width const width)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) m_width = width.m_n;
        return *this;
    }

    /**
     * @brief 设置填充字符，返回*this对象的引用
     */
    Log & operator<<(Fill const fill)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) m_flags.m_fill = fill.m_c;
        return *this;
    }

    /**
     * @brief 设置浮点数输出精度，返回*this对象的引用
     */
    Log & operator<<(Precision const precision)
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) m_precision = precision.m_n;
        return *this;
    }

    /**
     * @brief 日志输出格式控制
     *
     * @param op 操作函数
     *
     * @return 返回*this对象的引用
     */
    Log & operator<<(Log &(*op)(Log &))
    {
        if ((1u << m_flags.m_level) & m_flags.m_levelmask) op(*this);
        return *this;
    }

    /**
     * @brief 输出一个换行符，并flush缓冲区的数据到磁盘中，调用此函数来表示一条日志纪录的结束，返回log对象的引用
     */
    static Log & Endl(Log & log)
    {
        ++(log << '\n').Flush().m_nrecord;
        return log;
    }

    /**
     * @brief 修改日志输出的数字为16进制，返回log对象的引用
     */
    static Log & Hex(Log & log)
    {
        log.m_flags.m_base = HEX;
        return log;
    }

    /**
     * @brief 修改日志输出的数字为八进制，返回log对象的引用
     */
    static Log & Oct(Log & log)
    {
        log.m_flags.m_base = OCT;
        return log;
    }

    /**
    * @brief 修改日志输出的数字为十进制，返回log对象的引用
    */
    static Log & Dec(Log & log)
    {
        log.m_flags.m_base = DEC;
        return log;
    }

    /**
     * @brief 设置下一个输出为左对齐，在右边填充字符，返回log对象的引用
     */
    static Log & Left(Log & log)
    {
        log.m_flags.m_alignment = LEFT;
        return log;
    }

    /**
     * @brief 设置下一个输出为两端对齐，在符号与数值之间进行填充，返回log对象的引用
     */
    static Log & Internal(Log & log)
    {
        log.m_flags.m_alignment = INTERNAL;
        return log;
    }

    /**
     * @brief 设置下一个输出为右对齐，在左边填充字符，返回log对象的引用
     */
    static Log & Right(Log & log)
    {
        log.m_flags.m_alignment = RIGHT;
        return log;
    }

    /**
     * @brief 设置数值输出时自动添加进制前缀，返回log对象的引用
     */
    static Log & ShowBase(Log & log)
    {
        log.m_flags.m_showbase = 1;
        return log;
    }

    /**
     * @brief 将bool值输出为true，false字符串，返回log对象的引用
     */
    static Log & BoolAlpha(Log & log)
    {
        log.m_flags.m_boolalpha = 1;
        return log;
    }

    /**
     * @brief 设置浮点输出格式为fixed，返回log对象的引用
     */
    static Log & Fixed(Log & log)
    {
        log.m_flags.m_precision = FIXED;
        return log;
    }

    /**
     * @brief 设置浮点输出格式为scientific，返回log对象的引用
     */
    static Log & Scientific(Log & log)
    {
        log.m_flags.m_scientific = 1;
        return log;
    }

    /**
     * @brief 使用 log << SetW(n) 控制输出宽度，控制下一个输出的宽度
     *
     * @return 返回用于设置日志输出宽度的对象
     */
    static Width SetW(unsigned int const n) { return { n }; }

    /**
     * @brief 使用 log << SetFill(n) 设置填充字符
     *
     * @return 返回用于设置日志输出宽度的对象
     */
    static Fill SetFill(char const c) { return { c }; }

    /**
     * @brief 设置浮点型的输出精度
     *
     * @return 返回用于设置日志输出宽度的对象
     */
    static Precision SetPrecision(int const n) { return { n }; }

    /**
     * @brief 将缓冲区中的数据flush到磁盘
     *
     * @return 返回*this对象的引用
     */
    Log & Flush(void);

    /**
     * @brief 以C方式输出日志
     *
     * @param level 日志级别
     * @param tag 用户Tag，最大16字节长
     * @param format C风格的输出格式字符串
     * @param ... 输出参数列表
     *
     * @return 成功返回true，失败返回false
     */
    Log & Write(Level level, const char * tag, const char * format, ...);

    /**
     * @bref 获取格式标志位
     */
    FmtFlags Flags(void) const { return m_flags; }

    /**
     * @bref 设置新的格式标志位，返回旧的格式标志位
     */
    FmtFlags Flags(FmtFlags const flags)
    {
        auto const ret = m_flags;
        m_flags = flags;
        return ret;
    }

    /**
     * @bref 级别掩码setter与getter
     */
    void SetLevelMask(uint32_t const mask)
    {
        assert(mask <= ((1u << DBG) | (1u << INF) | (1u << WRN) | (1u << ERR)));
        m_flags.m_levelmask = 0x0F & mask;
    }

    uint32_t GetLevelMask(void) const { return m_flags.m_levelmask; }

protected:
    /**
     * @brief 限宽字符串，输出m_str最多不会超过m_width
     */
    struct WidthLimitedString
    {
        const char * m_str;
        size_t m_width;
    };

    /**
     * @brief 构造函数，生成module-YYYYMMDD.log的日志文件
     *
     * @param bufSize 内部缓冲区初始大小
     */
    Log(size_t bufSize = 4096);

    /**
     * @brief 输出有最大宽大限制的字符串
     */
    Log & operator<<(const WidthLimitedString & str) { return PutStr(str); }

    /**
     * @brief 获取日志Level字符串
     *
     * @param level 日志级别
     *
     * @return 返回日志Level字符串，不会返回NULL
     */
    static const char * LevelString(Level const level) { return s_levelString[level]; }

    /**
     * @brief 写日志前缀hh:mm:ss/level/tag
     */
    void MakePrefix(Level level, const char * tag);

    /**
     * @brief 生成日志文件
     *
     * @return 成功时返回true，失败时返回false
     */
    bool MakeNewLogFile(void);

    /**
     * @brief 检查文件日期
     *
     * @param tm 时间结构
     */
    void CheckFileDate(const tm & tm)
    {
        if (tm != m_fileDate)
        {
            Flush();
            MakeNewLogFile();
        }
    }

    /**
     * @brief 检查缓冲区剩余空间是否足够@size 字节，当空间不够时，将进行realloc
     */
    bool CheckBufferSpace(size_t size);

    /**
     * @brief 重载operator==操作符，比较日期是否相等
     */
    friend bool operator==(const Date & date, const tm & tm)
    {
        return date.m_day == tm.tm_mday && date.m_month == tm.tm_mon && date.m_year == tm.tm_year;
    }

    friend bool operator==(const tm & tm, const Date & date)
    {
        return date == tm;
    }

    friend bool operator!=(const Date & date, const tm & tm)
    {
        return !(date == tm);
    }

    friend bool operator!=(const tm & tm, const Date & date)
    {
        return date != tm;
    }

    /**
     * @brief 初始化加密相关的成员
     *
     * @param keystr 密码字符串
     */
    static void InitializeCrypto(const char * keystr);

    /**
     * @brief 输出长整数到缓冲区
     */
    Log & PutInteger(long long const ull)
    {
        static Log & (Log::*putFuncArray[])(unsigned long long) = { &Log::PutOct, &Log::PutSignedDec, &Log::PutHex };
        return (this->*putFuncArray[m_flags.m_base])(ull);
    }

    /**
     * @brief 输出无符号整数到缓冲区
     */
    Log & PutInteger(unsigned long long const ull)
    {
        static Log & (Log::*putFuncArray[])(unsigned long long) = { &Log::PutOct, &Log::PutUnsignedDec, &Log::PutHex };

        return (this->*putFuncArray[m_flags.m_base])(ull);
    }

    /**
     * @brief 输出八进制到缓冲区
     */
    Log & PutOct(unsigned long long ull);

    /**
     * @brief 输出十进制到缓冲区
     */
    Log & PutDec(unsigned long long ull, bool negative);

    /**
     * @brief 输出带符号十进制到缓冲区
     */
    Log & PutSignedDec(unsigned long long const ull) { return PutDec(ull, 0x8000000000000000u & ull); }

    /**
     * @brief 输出无符号十进制到缓冲区
     */
    Log & PutUnsignedDec(unsigned long long const ull) { return PutDec(ull, false); }

    /**
     * @brief 输出十六进制到缓冲区
     */
    Log & PutHex(unsigned long long ull);

    /**
     * @brief 输出浮点数到缓冲区
     */
    Log & PutDouble(double d);

    /**
     * @brief 输出一个字符到缓冲区
     */
    Log & PutChar(char c);

    /**
     * @brief 无视格式控制，直接输出一个字符
     */
    Log & PutChar(char c, DirectPut);

    /**
     * @brief 输出n个字符到缓冲区
     */
    Log & PutChar(size_t n, char c);

    /**
     * @brief 无视格式控制，输出n个字符到缓冲区
     */
    Log & PutChar(size_t n, char c, DirectPut);

    /**
     * @brief 输出字符串到缓冲区
     */
    Log & PutStr(const char * str, size_t len);

    /**
     * @brief 无视格式控制，输出字符串到缓冲区
     */
    Log & PutStr(const char * str, size_t len, DirectPut);

    /**
     * @brief 输出带长度限制的字符串
     */
    Log & PutStr(const WidthLimitedString & str);

    /**
     * @brief 将整数转换为十进制字符串，保存到缓冲区的结尾
     *
     * @param end 缓冲区结尾
     * @param ull 将被转换的整数
     *
     * @return 返回转换的字符串开头位置
     */
    static char * StringDec(char * end, unsigned long long ull);

    /**
     * @brief 将整数转换为八进制字符串，保存到缓冲区的结尾
     *
     * @param end 缓冲区结尾
     * @param ull 将被转换的整数
     *
     * @return 返回转换的字符串开头位置
     */
    static char * StringOct(char * end, unsigned long long ull);

    /**
     * @brief 将整数转换为十六进制字符串，保存到缓冲区的结尾
     *
     * @param end 缓冲区结尾
     * @param ull 将被转换的整数
     *
     * @return 返回转换的字符串开头位置
     */
    static char * StringHex(char * end, unsigned long long ull);

    /**
     * @brief 创建Log对象，使用Delete删除
     */
    static Log * Create(void)
    {
        return new Log; // TODO: use mempool allocate
    }

    /**
     * @brief 删除使用Create创建的对象
     */
    static void Delete(Log * log)
    {
        delete log;
    }

private:
    std::string     m_filename;   // 当前日志文件名
    std::ofstream   m_ofs;        // 文件流
    Date            m_fileDate;   // 文件日期
    size_t          m_nrecord;    // 日志纪录数
    FmtFlags        m_flags;      // 标志位
    size_t          m_width;      // 打印宽度
    size_t          m_precision;  // 浮点型精度
    Buffer          m_buffer;     // 日志缓冲区
    size_t          m_offset;     // 缓冲区写偏移
    size_t          m_size;       // 缓冲区大小

    static const size_t     MAX_TAG_LENGTH = 16;    // 最大Tag长度
    static std::string      s_workdir;              // 工作目录
    static std::string      s_module;               // 模块名称
    static bool             s_encrypt;              // 是否加密
    static AES_KEY          s_key;                  // AES密钥
    static initial_vector   s_iv;                   // AES初始向量
    static pthread_key_t    s_tlsKey;               // 线程本地存储索引
    static uint32_t         s_headerSize;           // 加密日志纪录头的大小
    static uint32_t         s_initialLevelMask;     // 初始级别掩码的全局设置，用于日志对象初始化
    static bool             s_initialized;          // 是否已初始化
};

#define sLog    Log::GetInstance()

/**
 * @brief 如果表达式为FALSE，则打印日志
 *
 * @param expr  表达式
 * @param log   日志对象
 * @param level 日志级别
 * @param tag   日志tag
 * @param fmt   C风格的日志格式化字符串
 * @param ...   日志格式化字符串中对应的变量列表
 */
#define CheckExprLog(expr, log, level, tag, fmt, ...)   \
    do {\
        if (!(expr)) {\
            log.Write(level, tag, fmt, ##__VA_ARGS__); \
        } \
    } while(0)

/**
 * @brief 如果表达式为FALSE，则打印日志，并返回值
 *
 * @param expr  表达式
 * @param ret   返回值
 * @param level 日志级别
 * @param tag   日志tag
 * @param fmt   C风格的日志格式化字符串
 * @param ...   日志格式化字符串中对应的变量列表
 */
#define CheckExprLogReturnValue(expr, ret, level, tag, fmt, ...) \
    do { \
        if (!(expr)) { \
            sLog.Write(level, tag, fmt, ##__VA_ARGS__); \
            return ret; \
        } \
    } while(0)


/**
 * @brief 如果表达式为FALSE，则打印日志，并返回void
 *
 * @param expr  表达式
 * @param level 日志级别
 * @param tag   日志tag
 * @param fmt   C风格的日志格式化字符串
 * @param ...   日志格式化字符串中对应的变量列表
 */
#define CheckExprLogReturnVoid(expr, level, tag, fmt, ...) \
    do { \
        if (!(expr)) { \
            sLog.Write(level, tag, fmt, ##__VA_ARGS__); \
            return; \
        } \
    } while(0)

 /**
  * @brief 如果表达式为FALSE，则打印日志，并abort
  *
  * @param expr  表达式
  * @param level 日志级别
  * @param tag   日志tag
  * @param fmt   C风格的日志格式化字符串
  * @param ...   日志格式化字符串中对应的变量列表
  */
#define CheckExprLogAbort(expr, level, tag, fmt, ...) \
    do { \
        if (!(expr)) { \
            sLog.Write(level, tag, fmt, ##__VA_ARGS__); \
            abort(); \
        } \
    } while(0)

 /**
  * @brief 如果表达式为FALSE，则打印日志，并exit
  *
  * @param expr  表达式
  * @param code  退出代码
  * @param level 日志级别
  * @param tag   日志tag
  * @param fmt   C风格的日志格式化字符串
  * @param ...   日志格式化字符串中对应的变量列表
  */
#define CheckExprLogExit(expr, code, level, tag, fmt, ...) \
    do { \
        if (!(expr)) { \
            sLog.Write(level, tag, fmt, ##__VA_ARGS__); \
            exit(code); \
        } \
    } while(0)
