#include <unistd.h>
#include <fcntl.h>

#include <cstdarg>
#include <cstring>
#include <ctime>
#include <system_error>

#include "Log.h"
#include "PasMD5.h"

const char * const Log::s_levelString[] = { "DBG", "INF", "WRN", "ERR" };

std::string         Log::s_workdir;
std::string         Log::s_module;
bool                Log::s_encrypt = false;
AES_KEY             Log::s_key;
Log::initial_vector Log::s_iv;
pthread_key_t       Log::s_tlsKey;
uint32_t            Log::s_headerSize = 0;
uint32_t            Log::s_initialLevelMask = 0x0F;
bool                Log::s_initialized = false;

bool Log::Initialize(
    const char * workdir,
    const char * module,
    uint32_t const initialLevelMask/* = 0x0F */,
    const char * key/* = nullptr */)
{
    if (s_initialized) return true;

    assert(module);

    // 设置工作目录
    if (workdir) { s_workdir.assign(workdir); }

    // 设置模块名称
    s_module.assign(module);

    // 初始化加密相关变量
    if (key && *key != '\0')
    {
        InitializeCrypto(key);
        s_encrypt = true;
        s_headerSize = 8;
    }

    s_initialLevelMask = initialLevelMask & 0x0F;

    // 申请线程本地存储索引
	auto const err = pthread_key_create(&s_tlsKey, reinterpret_cast<void(*)(void *)>(Delete));
    s_initialized = (err == 0);

    return s_initialized;
}

Log & Log::GetInstance(void)
{
    // 从线程本地存储区中获取与当前线程绑定的Log对象指针
    auto p = pthread_getspecific(s_tlsKey);

    if (!p)
    {
        // 创建日志对象
        p = Create();

        // 保存Log对象指针到线程本地存储区
        pthread_setspecific(s_tlsKey, p);
    }

    return *static_cast<Log *>(p);
}
Log & Log::Flush(void)
{
    if (m_offset == s_headerSize)
    {
        return *this;   // nothing to flush
    }

    if (s_encrypt)
    {
        auto const p = reinterpret_cast<uint8_t *>(m_buffer.Get()) + 8;     // 跳过8字节的头

        auto iv = s_iv;

        auto const msglen = m_offset - 8;

        AES_cbc_encrypt(
            p,
            p,
            msglen,
            &s_key,
            iv.data(),
            AES_ENCRYPT);

		*reinterpret_cast<uint32_t *>(p - 4) = msglen;
    }

    m_ofs.write(static_cast<char *>(m_buffer.Get()), m_offset);
    m_offset = s_headerSize;
    m_ofs.flush();
    return *this;
}

Log & Log::Write(Level const level, const char * tag, const char * format, ...)
{
    if (!((1u << uint32_t(level)) & m_flags.m_levelmask)) return *this;

    Flush()(level, tag);    // 先flush，再调用operator()写日志头

    auto buffer = static_cast<char *>(m_buffer.Get()) + m_offset;
    auto const bufsize = m_size - m_offset;

    va_list arg;
    va_start(arg, format);
    auto len = vsnprintf(buffer, bufsize, format, arg);
    va_end(arg);

    auto ret = false;

    if (len > 0)
    {
        if (size_t(len) > bufsize)   // buffer is too small, make a larger buffer and retry!
        {
            auto const expectSize = len + 1;
            auto const newSize = m_offset + expectSize;
            if (m_buffer.Realloc(newSize))
            {
                m_size = newSize;
                buffer = static_cast<char *>(m_buffer.Get()) + m_offset;
                va_start(arg, format);
                len = vsnprintf(buffer, expectSize, format, arg);
                va_end(arg);
                ret = len > 0;
            }
        }
        else
        {
            ret = true;
        }
    }


    if (ret)
    {
        m_offset += len;
        Flush();
    }

    return *this;
}

Log::Log(size_t bufSize)
    : m_fileDate({ 0, 0, 0 })
    , m_nrecord(0)
    , m_flags({ })
    , m_width(0)
    , m_precision(0)
    , m_offset(0)
{
    if (bufSize < 4096) bufSize = 4096;

    // alloc buffer
    if (!m_buffer.Realloc(bufSize)) return;

    m_size = bufSize;

    if (s_encrypt)
    {
        *static_cast<uint32_t *>(m_buffer.Get()) = 0xa1b2c3d4;  // set magic
        memset(static_cast<char *>(m_buffer.Get()) + 4, 0, 4);  // set length
        m_offset += 8;
    }

    // make log file
    auto const workdirLength = s_workdir.length();
    auto const moduleLength = s_module.length();

    const char suffix[] = "-yyyymmdd.log";

    // 预订空间
    m_filename.reserve(moduleLength + workdirLength + sizeof suffix + 2);

    // 构造日志文件路径模板
    m_filename.append(s_workdir);

    if (workdirLength > 0 && *s_workdir.rbegin() != '/')
    {
        m_filename.append(1, '/');
    }

    m_filename.append(s_module).append(suffix);

    // 创建新日志文件
    if (!MakeNewLogFile())
    {
        fprintf(stderr, "failed to create log file, file='%s', error='%m'\n", m_filename.c_str());
        exit(0);
    }

    // set flags
    m_flags.m_base = DEC;
    m_flags.m_alignment = RIGHT;
    m_flags.m_showbase = 0;
    m_flags.m_showpos = 0;
    m_flags.m_boolalpha = 0;
    m_flags.m_scientific = 0;
    m_flags.m_precision = DEFFLOAT;
    m_flags.m_levelmask = s_initialLevelMask;
    m_flags.m_fill = ' ';
}

void Log::MakePrefix(Level const level, const char * tag)
{
    auto const now = time(nullptr);

    tm tm;  // NOLINT
    localtime_r(&now, &tm);

    CheckFileDate(tm);

    *this << Right << SetFill('0') << Dec
          << SetW(2) << tm.tm_hour << ':' << SetW(2) << tm.tm_min << ':' << SetW(2) << tm.tm_sec << '/'
          << LevelString(level) << '/'
          << SetFill(' ') << Left << SetW(MAX_TAG_LENGTH) << WidthLimitedString{ tag, MAX_TAG_LENGTH } << ' ';
}

bool Log::MakeNewLogFile(void)
{
    tm tm;  // NOLINT

    // get current timestamp
    auto now = time(nullptr);

    localtime_r(&now, &tm);

    // make log file name
    sprintf(&m_filename[m_filename.length() - 12], "%04d%02d%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    // open a new log file
    m_ofs.close();
    m_ofs.open(m_filename, std::ios::app | std::ios::out | std::ios::binary);

    if (!m_ofs)
    {
        return false;
    }

    // save log file date
    m_fileDate = { tm.tm_year, tm.tm_mon, tm.tm_mday };

    return true;
}

bool Log::CheckBufferSpace(size_t size)
{
    auto const s = m_offset + size;

    if (s <= m_size)
    {
        return true;
    }

    if (m_buffer.Realloc(s))
    {
        m_size = s;
        return true;
    }

    return false;
}

void Log::InitializeCrypto(const char * keystr)
{
    assert(keystr);

    PasMD5 md5;
    unsigned char key[16];

    md5.MD5Update(reinterpret_cast<const unsigned char *>(keystr), strlen(keystr));

    md5.MD5Final(key);

    md5.MD5Update(key, 16);

    md5.MD5Final(s_iv.data());

    /*AES_set_encrypt_key(key, 16 * 8, &s_key);*/
}

Log & Log::PutOct(unsigned long long const ull)
{
    char buffer[64];

    auto const bufend = buffer + sizeof buffer;

    auto const pnum = StringOct(bufend, ull);

    size_t const numlen = bufend - pnum;

    auto const based_len = m_flags.m_showbase ? numlen + 1 : numlen;

    if (m_width <= based_len)
    {
        if (m_flags.m_showbase)
        {
            PutChar('0', DirectPut());
        }

        PutStr(pnum, numlen, DirectPut());
    }
    else
    {
        auto const npadding = m_width - based_len;

        if (m_flags.m_alignment == RIGHT || m_flags.m_alignment == INTERNAL) // right and internal
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());

            if (m_flags.m_showbase)
            {
                PutChar('0', DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());
        }
        else // left
        {
            if (m_flags.m_showbase)
            {
                PutChar('0', DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());

            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutDec(unsigned long long ull, bool const negative)
{
    char buffer[64];

    auto const bufend = buffer + sizeof buffer;

    auto sgn = '+';

    if (negative)
    {
        sgn = '-';
        ull = -ull;
    }

    auto const pnum = StringDec(bufend, ull);

    size_t const numlen = bufend - pnum;

    auto const sgn_num_len = (negative || m_flags.m_showpos) ? numlen + 1 : numlen;

    if (m_width <= sgn_num_len)
    {
        if (negative || m_flags.m_showpos)
        {
            PutChar(sgn, DirectPut());
        }

        PutStr(pnum, numlen, DirectPut());
    }
    else
    {
        auto const npadding = m_width - sgn_num_len;

        if (m_flags.m_alignment == RIGHT) // right alignment
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());

            if (negative || m_flags.m_showpos)
            {
                PutChar(sgn, DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());
        }
        else if (m_flags.m_alignment == INTERNAL)    // internal align
        {
            if (negative || m_flags.m_showpos)
            {
                PutChar(sgn, DirectPut());
            }

            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutStr(pnum, numlen, DirectPut());
        }
        else
        {
            if (negative || m_flags.m_showpos)
            {
                PutChar(sgn, DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutHex(unsigned long long const ull)
{
    char buffer[64];

    auto const bufend = buffer + sizeof buffer;

    auto const pnum = StringHex(bufend, ull);

    size_t const numlen = bufend - pnum;

    auto const based_len = m_flags.m_showbase ? numlen + 2 : numlen;

    if (m_width <= based_len)
    {
        if (m_flags.m_showbase)
        {
            PutStr("0x", 2, DirectPut());
        }

        PutStr(pnum, numlen, DirectPut());
    }
    else
    {
        auto const npadding = m_width - based_len;

        if (m_flags.m_alignment == RIGHT) // right
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());

            if (m_flags.m_showbase)
            {
                PutStr("0x", 2, DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());
        }
        else if (m_flags.m_alignment == INTERNAL)    // internal
        {
            if (m_flags.m_showbase)
            {
                PutStr("0x", 2, DirectPut());
            }

            PutChar(npadding, m_flags.m_fill, DirectPut());

            PutStr(pnum, numlen, DirectPut());
        }
        else    // left
        {
            if (m_flags.m_showbase)
            {
                PutStr("0x", 2, DirectPut());
            }

            PutStr(pnum, numlen, DirectPut());

            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutDouble(double const d)
{
    static const char * s_fmt[][4] = {
        { "%f", "%.*f", "%.*f", "%.*f" },   // non-scientific { DEFFLOAT, FIXED, PRECISE, PRECISE }
        { "%e", "%.*e", "%.*e", "%.*f" }    // scientific     { DEFFLOAT, FIXED, PRECISE, PRECISE }
    };

    char buffer[64];

    auto const fmt = s_fmt[m_flags.m_scientific][m_flags.m_precision];

    size_t len;

    if (m_flags.m_precision == DEFFLOAT)
    {
        len = sprintf(buffer, fmt, d);
    }
    else
    {
        auto const precision = (m_flags.m_precision == FIXED) ? 16 : m_precision;
        len = sprintf(buffer, fmt, precision, d);
    }

    if (m_width <= len)
    {
        PutStr(buffer, len, DirectPut());
    }
    else
    {
        auto sgn = '+';

        auto p = buffer;

        if (d < 0)
        {
            ++p;
            --len;
            sgn = '-';
        }

        auto const signed_len = (d < 0 || m_flags.m_showpos) ? len + 1 : len;

        auto const npadding = m_width - signed_len;

        if (m_flags.m_alignment == RIGHT)
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutChar(sgn, DirectPut());
            PutStr(p, len, DirectPut());
        }
        else if (m_flags.m_alignment == INTERNAL)
        {
            PutChar(sgn, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutStr(p, len, DirectPut());
        }
        else
        {
            PutChar(sgn, DirectPut());
            PutStr(p, len, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutChar(char const c)
{
    if (m_width <= 1)
    {
        PutChar(c, DirectPut());
    }
    else
    {
        auto const npadding = m_width - 1;

        if (m_flags.m_alignment == LEFT)
        {
            PutChar(c, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
        else
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutChar(c, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutChar(char const c, DirectPut)
{
    if (!CheckBufferSpace(sizeof c))
    {
        // TODO: Insufficient memory
        return *this;
    }

    static_cast<char *>(m_buffer.Get())[m_offset++] = c;
    return *this;
}

Log & Log::PutChar(size_t n, char const c)
{
    if (m_width <= n)
    {
        PutChar(n, c, DirectPut());
    }
    else
    {
        auto const npadding = m_width - n;

        if (m_flags.m_alignment == LEFT)
        {
            PutChar(n, c, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
        else
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutChar(n, c, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutChar(size_t const n, char const c, DirectPut)
{
    if (!CheckBufferSpace(n * sizeof c))
    {
        // TODO: Insufficient memory
        return *this;
    }

    memset(static_cast<char *>(m_buffer.Get()) + m_offset, c, n);
    m_offset += n;
    return *this;
}

Log & Log::PutStr(const char * str, size_t const len)
{
    if (m_width <= len)
    {
        PutStr(str, len, DirectPut());
    }
    else
    {
        auto const npadding = m_width - len;

        if (m_flags.m_alignment == LEFT)
        {
            PutStr(str, len, DirectPut());
            PutChar(npadding, m_flags.m_fill, DirectPut());
        }
        else
        {
            PutChar(npadding, m_flags.m_fill, DirectPut());
            PutStr(str, len, DirectPut());
        }
    }

    m_width = 0;
    return *this;
}

Log & Log::PutStr(const char * str, size_t const len, DirectPut)
{
    if (!CheckBufferSpace(len))
    {
        // TODO: Insufficient memory
        return *this;
    }

    memcpy(static_cast<char *>(m_buffer.Get()) + m_offset, str, len);
    m_offset += len;
    return *this;
}

Log & Log::PutStr(const WidthLimitedString & str)
{
    assert(str.m_str);
    auto const len = strlen(str.m_str);
    return PutStr(str.m_str, std::min(len, str.m_width));
}

char * Log::StringDec(char * end, unsigned long long ull)
{
    do
    {
        *--end = '0' + ull % 10;
        ull /= 10;
    } while (ull > 0);

    return end;
}

char * Log::StringOct(char * end, unsigned long long ull)
{
    do
    {
        *--end = '0' + (ull & 7);
        ull >>= 3;
    }
    while (ull > 0);

    return end;
}

char * Log::StringHex(char * end, unsigned long long ull)
{
    static const char hex_table[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

    do
    {
        *--end = hex_table[ull & 15];
        ull >>= 4;
    }
    while (ull > 0);

    return end;
}
