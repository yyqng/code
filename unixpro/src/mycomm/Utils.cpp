////////////////////////////////////////////////////////////////////////////////
///
/// @file Utils.cpp
///
/// @brief Utility APIs definition.
///
/// Utility APIs provide some useful functions.
///
////////////////////////////////////////////////////////////////////////////////

#include <errno.h>
#include <sys/stat.h>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <sys/syscall.h>
#include <algorithm>  //transform in MacFormatCheck
#include <string.h>
#include "Utils.hpp"


int StringMapInt(StringIntMap* maps, const std::string& str, bool isIgnCase)
{
    StringIntMap* map = maps;
    while (true)
    {
        if (NULL == map->str)
        {
            return map->value;
        }

        int rc = 0;
        if (isIgnCase)
        {
            rc = strcasecmp(map->str, str.data());
        }
        else
        {
            rc = strcmp(map->str, str.data());
        }

        if (0 == rc)
        {
            return map->value;
        }

        ++map;
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
ThreadMutex::ThreadMutex():
    m_lockThreadId(0),
    m_lockCnt(0)
{
    // initialize mutex
    pthread_mutex_init(&m_mutex, NULL);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
ThreadMutex::~ThreadMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void ThreadMutex::LockOnce()
{
    pthread_mutex_lock(&m_mutex);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void ThreadMutex::UnlockOnce()
{
    pthread_mutex_unlock(&m_mutex);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void ThreadMutex::LockMulti()
{
    pthread_t thisThreadId = pthread_self();

    if (m_lockThreadId != thisThreadId)
    {
        pthread_mutex_lock(&m_mutex);

        m_lockThreadId = thisThreadId;
    }
    ++m_lockCnt;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void ThreadMutex::UnlockMulti()
{
    if (m_lockCnt > 0)
    {
        --m_lockCnt;

        if (0 == m_lockCnt)
        {
            m_lockThreadId = 0;
            pthread_mutex_unlock(&m_mutex);
        }
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
StringToValue::StringToValue():
m_type(VALUE_INT),
m_string("")
{
    memset(&m_value, 0, sizeof(m_value));
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
StringToValue::~StringToValue()
{
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
StringToValue& StringToValue::operator=(const StringToValue& rhs)
{
    SetType(rhs.GetType());
    SetValue(rhs.GetValueString());

    return *this;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void StringToValue::SetType(ValueType type)
{
    m_type = type;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void StringToValue::SetValue(const std::string& valueString)
{
    m_string = valueString;
    memset(&m_value, 0, sizeof(m_value));

    switch (m_type)
    {
        case VALUE_INT:
            m_value.vInt = strtol(m_string.data(), NULL, 0);
            break;

        case VALUE_STRING:
            m_value.vString = m_string.data();
            break;

        case VALUE_IPADDR:
            inet_aton(m_string.data(), &m_value.vIpaddr);
            break;

        default:
            break;
    }

}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
ValueType StringToValue::GetType() const
{
    return m_type;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
bool StringToValue::HasValue() const
{
    return !m_string.empty();
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
const std::string& StringToValue::GetValueString() const
{
    return m_string;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int StringToValue::GetValueAsInt() const
{
    return m_value.vInt;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
const char* StringToValue::GetValueAsString() const
{
    return m_value.vString;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
in_addr_t StringToValue::GetValueAsIpAddr() const
{
    return m_value.vIpaddr.s_addr;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const StringToValue& rhs)
{
    switch (rhs.GetType())
    {
        case VALUE_INT:
            os << rhs.GetValueAsInt();
            break;

        case VALUE_STRING:
            os << rhs.GetValueAsString();
            break;

        case VALUE_IPADDR:
            os << IpV4ToString(rhs.GetValueAsIpAddr());
            break;

        default:
            os << "unknown value type";
            break;
    }

    return os;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
FileTime::FileTime()
{
    ClearTime();
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
FileTime::~FileTime()
{
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int FileTime::SetFile(const std::string& fileName)
{
    ClearTime();

    m_fileName = fileName;

    UpdateTime();

    return 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
bool FileTime::UpdateTime(bool atime, bool mtime, bool ctime)
{
    struct stat buf;
    if (stat(m_fileName.data(), &buf))
    {
        return false;
    }

    bool isChange = false;

    if (atime)
    {
        if (m_atime != buf.st_atime)
        {
            isChange = true;
            m_atime = buf.st_atime;
        }
    }

    if (mtime)
    {
        if (m_mtime != buf.st_mtime)
        {
            isChange = true;
            m_mtime = buf.st_mtime;
        }
    }

    if (ctime)
    {
        if (m_ctime != buf.st_ctime)
        {
            isChange = true;
            m_ctime = buf.st_ctime;
        }
    }

    return isChange;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief Clear file time
/// @return none
////////////////////////////////////////////////////////////////////////////////
void FileTime::ClearTime()
{
    m_atime = 0;
    m_mtime = 0;
    m_ctime = 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string IpV4ToString(in_addr_t ip)
{
    struct in_addr in;
    in.s_addr = ip;
    return inet_ntoa(in);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetDirName(const std::string& fileName)
{
    // find last '/'
    int pos = fileName.rfind("/");
    if (pos != -1)
    {
        return fileName.substr(0, pos+1);
    }
    else
    {
        return "";
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetBaseName(const std::string& fileName)
{
    // find last '/'
    int pos = fileName.rfind("/");
    if (pos != -1)
    {
        return fileName.substr(pos+1);
    }
    else
    {
        return fileName;
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetSuffix(const std::string& fileName)
{
    // find last '.'
    int pos = fileName.rfind(".");
    if (pos != -1)
    {
        return fileName.substr(pos+1);
    }
    else
    {
        return "";
    }
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void SplitFileName(const std::string& fileFullName,
                   std::string* path,
                   std::string* file,
                   std::string* fileName,
                   std::string* fileExt)
{
    std::string dirName;
    std::string baseName;
    std::string prefix;
    std::string postfix;

    // find last '/'
    int pos = fileFullName.rfind("/");
    if (pos != -1)
    {
        dirName = fileFullName.substr(0, pos+1);
        baseName = fileFullName.substr(pos+1);
    }
    else
    {
        dirName = "./";
        baseName = fileFullName;
    }

    // find last '.'
    pos = baseName.rfind('.');
    if (pos != -1)
    {
        prefix = baseName.substr(0, pos);
        postfix = baseName.substr(pos+1);
    }
    else
    {
        prefix = baseName;
        postfix = "";
    }

    if (path != NULL)
    {
        *path = dirName;
    }

    if (file != NULL)
    {
        *file = baseName;
    }

    if (fileName != NULL)
    {
        *fileName = prefix;
    }

    if (fileExt != NULL)
    {
        *fileExt = postfix;
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int CreateDir(const char* path)
{
    if (NULL == path)
    {
        return -1;
    }

    std::string fullPath = path;

    int rc = 0;
    int pos = 0;
    std::string levelPath;

    while (true)
    {
        pos = fullPath.find("/", pos);

        if (pos != 0)
        {
            levelPath = fullPath.substr(0, pos);
            rc = ::mkdir(levelPath.data(), 0777);
            if (rc && (errno != EEXIST))
            {
                return -1;
            }
        }

        if (pos != -1)
        {
            pos++;
        }
        else
        {
            break;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string AdjustPath(const std::string& path, bool ends)
{
    std::string out = "";

    const char* p = path.data();
    int len = path.size();
    char last = 0;
    char c = 0;
    char sep = '/';

    for (int i = 0; i < len; ++i)
    {
        c = *(p+i);

        if ((c != sep) || (last != sep))
        {
            out += c;
            last = c;
        }
    }

    if (ends)
    {
        if (last != sep)
        {
            out += sep;
        }
    }

    return out;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
bool IsFileExist(const char* file)
{
    if (NULL == file)
    {
        return false;
    }

    struct stat buf;

    if (stat(file, &buf))
    {
        return false;
    }
    else
    {
        return true;
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
ssize_t GetFileSize(const char* file)
{
    if (NULL == file)
    {
        return -1;
    }

    struct stat buf;

    if (stat(file, &buf))
    {
        return -1;
    }
    else
    {
        return buf.st_size;
    }
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int CreateFile(const char* file)
{
    if (NULL == file)
    {
        return -1;
    }

    if (IsFileExist(file))
    {
        return -1;
    }

    FILE* fp = fopen(file, "w");
    if (NULL == fp)
    {
        std::string dir = GetDirName(file);

        CreateDir(dir.data());
        fp = fopen(file, "w");
        if (NULL == fp)
        {
            PERROR("Failed to create file %s", file);
            return -1;
        }
    }

    fclose(fp);

    return 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void PrintError(const char* file, const int line, const char* format, ... )
{
    char buf[1024] = "";
    char* out = buf;
    int size = sizeof(buf)-1;

    int rc = snprintf(out, size, "%s:%d ", file, line);
    size -= rc;
    out += rc;

    va_list ap;
    va_start(ap, format);
    vsnprintf(out, size, format, ap);
    va_end(ap);

    ::perror(buf);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int StringSplitByChar(const char* begin, const char* end, const char* sep, VectorString& result)
{
    if ((NULL == begin) || (NULL == sep))
    {
        return -1;
    }

    result.clear();

    const char* p = begin;
    char c;
    std::string s;

    while (((NULL == end) || (p < end)) && ((c = *p++) != '\0'))
    {
        if (NULL == strchr(sep, c))
        {
            s += c;
        }
        else
        {
            // 空字符也要输出
            result.push_back(s);
            s.clear();
        }
    }

    result.push_back(s);
    s.clear();

    return 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int StringSplitByString(const char* begin, const char* end, const char* sep, VectorString& result)
{
    if ((NULL == begin) || (NULL == sep))
    {
        return -1;
    }

    result.clear();

    const char* p = begin;
    const char* pend = end;
    const char* find = NULL;
    size_t sepLen = strlen(sep);
    std::string s;

    if (NULL == pend)
    {
        pend = p + strlen(p);
    }

    while (p < pend)
    {
        find = std::search(p, pend, sep, sep+sepLen);

        if (pend == find)
        {
            s.assign(p, pend-p);
            result.push_back(s);
            break;
        }
        else
        {
            s.assign(p, find-p);
            result.push_back(s);

            p = find + sepLen;
        }
    }

    return 0;
}

int StringSplitInclude0(const char* begin, const char* end, const char* sep, VectorString& result)
{
    if ((NULL == begin) || (NULL == sep))
    {
        return -1;
    }

    result.clear();

    const char* p = begin;
    char c;
    std::string s;

    while (((NULL == end) || (p < end)))
    {
        c = *p++;
        if (NULL == strchr(sep, c))
        {
            s += c;
        }
        else
        {
            result.push_back(s);
            s.clear();
        }
    }

    result.push_back(s);
    s.clear();

    return 0;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string StringTrim(const std::string& src, const std::string& left, const std::string& right)
{
    const char* lstr = src.data();
    const char* rstr = lstr + src.length();

    if (!left.empty())
    {
        while (lstr < rstr)
        {
            if (0 == strncmp(lstr, left.data(), left.length()))
            {
                lstr += left.length();
            }
            else
            {
                break;
            }
        }
    }

    if (!right.empty())
    {
        const char* p = rstr - right.length();

        while (lstr < p)
        {
            if (0 == strncmp(p, right.data(), right.length()))
            {
                rstr = p;
                p = rstr - right.length();
            }
            else
            {
                break;
            }
        }
    }

    return std::string(lstr, rstr-lstr);
}


std::string ReplaceString(const std::string &sSrc, const std::string &sFilter, const std::string &sNew)
{   
    if ((sSrc.empty()) || (sFilter.empty()))
    {
        return sSrc;
    }
    
    std::string out = "";
    const char* from = sSrc.data();
    const char* p = NULL;
    const char* filter = sFilter.data();
    size_t filterLen = sFilter.length();
  
    while (true)
    {
        p = strstr(from, filter);
        if (NULL == p)
        {
            break;
        }
        
        out.append(from, p-from);
        out += sNew;
        from = p + filterLen;
    } 
    
    out.append(from);

	return out;
}

std::string RemoveCrLf(const std::string& line)
{
    std::string out = "";
    
    out = ReplaceString(line, "\r", "");
    out = ReplaceString(line, "\n", "");

    return out;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
size_t MemSpn(const char* begin, const char* end, const char* accept, size_t acceptNum)
{
    if ((NULL == begin) || (NULL == end) || (NULL == accept) || (0 == acceptNum))
    {
        return 0;
    }

    const char* p = begin;

    while (p < end)
    {
        char c = *p;
        bool isAccept = false;

        for (size_t i = 0; i < acceptNum; ++i)
        {
            if (c == accept[i])
            {
                isAccept = true;
                break;
            }
        }

        if (isAccept)
        {
            ++p;
        }
        else
        {
            break;
        }
    }

    return (p - begin);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
size_t MemCspn(const char* begin, const char* end, const char* reject, size_t rejectNum)
{
    if ((NULL == begin) || (NULL == end) || (NULL == reject) || (0 == rejectNum))
    {
        return 0;
    }

    const char* p = begin;

    while (p < end)
    {
        char c = *p;

        for (size_t i = 0; i < rejectNum; ++i)
        {
            if (c == reject[i])
            {
                return (p - begin);
            }
        }

        ++p;
    }

    return (p - begin);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int ReadConfigFile(const std::string& file, const std::string& key, VectorString& value)
{
    char line[1024];
    bool isFound = false;

    FILE* fp = fopen(file.data(), "r");
    if (NULL == fp)
    {
        return -1;
    }

    while (fgets(line, sizeof(line)-1, fp))
    {
        char* pos = strchr(line, '#');
        if (pos != NULL)
        {
            *pos = '\0';
        }

        value.clear();

        if (StringSplitByChar(line, NULL, " ", value) ||
            (0 == value.size()))
        {
            continue;
        }

        if (key == value[0])
        {
            isFound = true;
            break;
        }
    }

    fclose(fp);

    if (isFound)
    {
        return 0;
    }
    else
    {
        value.clear();
        return -1;
    }

}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int GetRand(int min, int max)
{
    if (min > max)
    {
        return 0;
    }
    else if (min == max)
    {
        return min;
    }

    static bool isInit = false;

    if (!isInit)
    {
        isInit = true;
        ::srand((int)time(0));
    }

    double scale = max - min + 1;
    int value = ::rand();
    value = (int)(scale/(RAND_MAX+1.0)*value) + min;

    return value;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::ostream& DumpData(std::ostream& out,
                       const void* data,
                       size_t size,
                       const void* printAddr,
                       bool hasAddr,
                       bool hasHex,
                       bool hasChar)
{
    const char* start = (const char*)data;
    const char* end = (const char*)data + size;
    off_t offset = (off_t)printAddr;

    const char* p = start;

    while (p < end)
    {
        std::ostringstream addrStr;
        std::ostringstream hexStr;
        std::ostringstream charStr;
        char line[80];

        sprintf(line, "%08lX:", p - start + offset);
        addrStr << line;

        int no = 0;
        while (no < 16)
        {
            if (p >= end)
            {
                hexStr << "   ";
                charStr << " ";
            }
            else
            {
                unsigned char ch = *p;

                sprintf(line, "%02X ", ch);
                hexStr << line;

                if (isprint(ch))
                {
                    charStr << ch;
                }
                else
                {
                    charStr << ".";
                }
            }

            if (7 == no)
            {
                hexStr << " ";
            }

            ++no;
            ++p;
        }

        if (hasAddr)
        {
            out << addrStr.str() << "  ";
        }

        if (hasHex)
        {
            out << hexStr.str() << "  ";
        }

        if (hasChar)
        {
            out << charStr.str() << std::endl;
        }
    }

    return out;
}

StringBuffer::StringBuffer(size_t bufLen)
{
    m_bufLen = bufLen;

    size_t newLen = m_bufLen + 1;
    m_buf = new char[newLen];
    memset(m_buf, 0, newLen);

    m_str = "";
}

StringBuffer::~StringBuffer()
{
    if (m_buf != NULL)
    {
        delete[] m_buf;
        m_buf = NULL;
    }
}

void StringBuffer::Clear()
{
    m_str = "";
}

const std::string& StringBuffer::GetString() const
{
    return m_str;
}

StringBuffer& StringBuffer::Set(const std::string& v)
{
    m_str = v;

    return *this;
}

StringBuffer& StringBuffer::Add(const std::string& v)
{
    m_str += v;

    return *this;
}

StringBuffer& StringBuffer::Set(const char* format, ...)
{
    if (NULL == format)
    {
        return *this;
    }

    va_list ap;
    va_start(ap, format);
    vsnprintf(m_buf, m_bufLen, format, ap);
    va_end(ap);

    m_str = m_buf;

    return *this;
}

StringBuffer& StringBuffer::Add(const char* format, ...)
{
    if (NULL == format)
    {
        return *this;
    }

    va_list ap;
    va_start(ap, format);
    vsnprintf(m_buf, m_bufLen, format, ap);
    va_end(ap);

    m_str += m_buf;

    return *this;
}

StringBuffer& StringBuffer::operator=(const StringBuffer& v)
{
    if (&v != this)
    {
        m_str = v.GetString();
    }

    return *this;
}

StringBuffer& StringBuffer::operator<<(const StringBuffer& v)
{
    m_str += v.GetString();

    return *this;
}

StringBuffer& StringBuffer::operator<<(char v)
{
    Add("%c", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(unsigned char v)
{
    Add("%u", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(short v)
{
    Add("%d", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(unsigned short v)
{
    Add("%u", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(int v)
{
    Add("%d", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(unsigned int v)
{
    Add("%u", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(long v)
{
    Add("%ld", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(unsigned long v)
{
    Add("%lu", v);

    return *this;
}

StringBuffer& StringBuffer::operator<<(const std::string& v)
{
    m_str += v;

    return *this;
}




//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
const char* GetProcFullName()
{
    static std::string name = "";

    if (name.empty())
    {
        char path[128] = "";
        char link[1024] = "";

        sprintf(path, "/proc/%d/exe" ,getpid());
        ssize_t rc = readlink(path, link, sizeof(link)-1);
        if (rc > 0)
        {
            name.append(link, rc);
        }
    }

    return name.data();
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
const char* GetProcBaseName(const char* fullName)
{
    static std::string name = "";

    if (name.empty())
    {
        if (NULL == fullName)
        {
            name = GetBaseName(GetProcFullName());
        }
        else
        {
            name = GetBaseName(fullName);
        }
    }

    return name.data();
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
const char* GetProcPathName(const char* fullName)
{
    static std::string name = "";

    if (name.empty())
    {
        if (NULL == fullName)
        {
            name = GetDirName(GetProcFullName());
        }
        else
        {
            name = GetDirName(fullName);
        }
    }

    return name.data();
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
bool IsValidAddress(const void* address, int size)
{
    if (mlock(address, size))
    {
        return false;
    }

    munlock(address, size);

    return true;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int CopyFile(const char* src, const char* dst)
{
    FILE* srcFp = NULL;
    FILE* dstFp = NULL;
    const size_t bufSize = 1024;
    char buf[bufSize] = "";
    size_t size = 0;
    size_t totalSize = 0;
    int rc = 0;

    do
    {
        srcFp = fopen(src, "rb");
        if (NULL == srcFp)
        {
            rc = -1;
            break;
        }

        dstFp = fopen(dst, "wb");
        if (NULL == dstFp)
        {
            rc = -1;
            break;
        }

        while (1)
        {
            size = fread(buf, 1, bufSize, srcFp);
            if (0 == size)
            {
                break;
            }

            if (fwrite(buf, 1, size, dstFp) != size)
            {
                rc = -1;
                break;
            }

            totalSize += size;
        }
    }
    while(0);

    if (srcFp != NULL)
    {
        fclose(srcFp);
    }

    if (dstFp != NULL)
    {
        fclose(dstFp);
    }

    return rc;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int MoveFile(const char* oldName, const char* newName)
{
    if ((NULL == oldName) || (NULL == newName))
    {
        return -1;
    }

    int rc = rename(oldName, newName);
    if (rc < 0)
    {
        rc = CopyFile(oldName, newName);
        if (rc < 0)
        {
            return -1;
        }
        unlink(oldName);
    }

    return 0;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
double GetTimeAsDouble(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL))
    {
        return 0;
    }

    return (time.tv_sec + time.tv_usec * 1.0 / MICRO_SECOND);
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetTimeString(time_t tt)
{
    struct tm *times = localtime(&tt);
    char buf[80];

    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",
             times->tm_year+1900,
             times->tm_mon + 1,
             times->tm_mday,
             times->tm_hour,
             times->tm_min,
             times->tm_sec);

    return buf;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
time_t MakeTime(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm tmTime;
    memset(&tmTime, 0, sizeof(tmTime));

    tmTime.tm_year = year - 1900;
    tmTime.tm_mon = mon - 1;
    tmTime.tm_mday = day;
    tmTime.tm_hour = hour;
    tmTime.tm_min = min;
    tmTime.tm_sec = sec;

    time_t time = mktime(&tmTime);

    return time;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
time_t StrToTime(const char *date,const char * format)
{
	if(date == NULL)
	{
		return 0;
	}

	struct tm tm;
	strptime(date,format,&tm);
	time_t ft = mktime(&tm);
	return ft;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
void SleepInDouble(double seconds)
{
    struct timespec req;
    struct timespec rem;

    req.tv_sec = (long)seconds;
    req.tv_nsec = (long)((seconds - req.tv_sec) * NANO_SECOND);

    while (nanosleep(&req, &rem))
    {
        req = rem;
    }
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string HexIntToString(const void* p, int len)
{
    bool isIgnZero = true;
    std::string out = "";
    const char* v = (const char*)p;

    for (int i = 0; i < len; ++i)
    {
        char tmp[10] = "";
        uint8_t c = *(v+i);

        if (isIgnZero)
        {
            if (c != '\0')
            {
                isIgnZero = false;
                sprintf(tmp, "%x", c);
            }
        }
        else
        {
            sprintf(tmp, "%02x", c);
        }

        out += tmp;
    }

    return out;
}


//------------------------------------------------------------------------------
// This is a public API.  0x8  ==> 08
//------------------------------------------------------------------------------
std::string HexIntToString_v2(const void* p, int len)
{
    std::string out = "";
    const char* v = (const char*)p;

    for (int i = 0; i < len; ++i)
    {
        char tmp[10] = "";
        uint8_t c = *(v+i);
        sprintf(tmp, "%02x", c);
        out += tmp;
    }

    return out;
}

std::string HexIntToString_v2(const std::string& in)
{
    std::string out = "";
    const char* v = in.data();

    for (unsigned int i = 0; i < in.length(); ++i)
    {
        char tmp[10] = "";
        uint8_t c = *(v+i);
        sprintf(tmp, "%02x", c);
        out += tmp;
    }

    return out;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::vector<char> HexStrToBin(const std::string& s)
{
    static unsigned char maps[] =
    {
        0,1,2,3,4,5,6,7,8,9,            // 0-9
        0,0,0,0,0,0,0,
        10,11,12,13,14,15,              // A-F
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,
        10,11,12,13,14,15,              // a-f
    };

    size_t len = s.length();
    const char* p = s.data();
    const char* end = p + len;
    std::vector<char> out;

    for (size_t i = 0; i < len; ++i)
    {
        if (!isxdigit(*(p+i)))
        {
            return out;
        }
    }

    if (len % 2)
    {
        out.push_back(maps[*p-'0']);
        ++p;
    }

    while (p < end)
    {
        out.push_back((maps[*p-'0']<<4)|maps[*(p+1)-'0']);
        p += 2;
    }

    return out;
}

void StrToHex(std::string& out, unsigned char* pSrc, size_t size)
{
    char h1, h2;
    unsigned s1, s2;
    size_t i;

    for(i=0; i < size; i++)
    {
        h1 = pSrc[2*i];
        h2 = pSrc[2*i+1];

        s1 = toupper(h1) - 0x30;
        if(s1 > 9)
            s1 -=7;
        s2=toupper(h2) - 0x30;
        if(s2 > 9)
            s2 -=7;

        unsigned char tmp = s1*16 + s2;
        out.append(1, tmp);
    }
}

uint64_t RoundPower2(uint64_t n)
{
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return n + 1;
}


//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int GetMultiProcessNum(const char* name)
{
    if (NULL == name)
    {
        return -1;
    }

    std::string procName = GetBaseName(name);
    std::string command = "ps -e c | grep -w -c ";
    command += procName;

    FILE* fp = popen(command.data(), "r");
    if (NULL == fp)
    {
        return (-2);
    }

    char line[13] = "";
    if (NULL == fgets(line, sizeof(line), fp))
    {
        return (-3);
    }

#if 0
    int status = pclose(fp);

    if (0 == WIFEXITED(status))
    {
        return (-4);
    }
#else
    pclose(fp);
#endif

    return atoi(line);

}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
size_t StringToSize(const char* data)
{
    if (NULL == data)
    {
        return 0;
    }

    char* end = NULL;

    size_t size = strtoul(data, &end, 0);

    if (end != NULL)
    {
        char c = *end;

        switch (c)
        {
            case 'k':
            case 'K':
                size <<= 10;
                break;

            case 'm':
            case 'M':
                size <<= 20;
                break;

            case 'g':
            case 'G':
                size <<= 30;
                break;

            case 't':
            case 'T':
                size <<= 40;
                break;
        }
    }

    return size;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetLastTime(double t)
{
    size_t minSeconds = 60;
    size_t hourSeconds = minSeconds * 60;
    size_t daySeconds = hourSeconds * 24;

    size_t last = (size_t)(t>0?t:(-t));

    int days = last / daySeconds;
    last -= days * daySeconds;

    int hours = last / hourSeconds;
    last -= hours * hourSeconds;

    int mins = last / minSeconds;
    last -= mins * minSeconds;

    int secs = last;

    char buf[80];
    snprintf(buf, sizeof(buf)-1, "%d days, %02d:%02d:%02d", days, hours, mins, secs);

    return buf;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string IntToString(long value, const char* format)
{
    char buf[80] = "";

    if (NULL == format)
    {
        format = "%ld";
    }

    sprintf(buf, format, value);

    return buf;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
int GetLinuxSwapInfo(size_t* total, size_t* free, size_t* used)
{
    std::ifstream fin("/proc/meminfo");
    if (!fin.good())
    {
        return -1;
    }

    size_t stotal = 0;
    size_t sfree = 0;

    while(!fin.eof())
    {
        std::string line;
        std::string tag;

        getline(fin, line);
        std::istringstream sin(line);
        sin >> tag;

        if ("SwapTotal:" == tag)
        {
            sin >> stotal;
        }
        else if ("SwapFree:" == tag)
        {
            sin >> sfree;
        }
    }

    fin.close();

    stotal *= 1024;
    sfree *= 1024;

    if (total != NULL)
    {
        *total = stotal;
    }

    if (free != NULL)
    {
        *free = sfree;
    }

    if (used != NULL)
    {
        *used = stotal-sfree;
    }

    return 0;
}

#if 0
//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
pid_t gettid()
{
    return syscall(SYS_gettid);
}
#endif

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
pid_t gettid(pthread_t thid)
{
    struct pthread_t_fake
    {
        char s[144];
        pid_t tid;
        pid_t pid;
    };

    pthread_t_fake* f = (pthread_t_fake*)thid;
    return f->tid;
}

//------------------------------------------------------------------------------
// This is a public API.
//------------------------------------------------------------------------------
std::string GetStack(pid_t pid)
{
    char buf[80] = "";
    snprintf(buf, sizeof(buf)-1, "pstack %d", pid);

    FILE* fp = popen(buf, "r");
    if (NULL == fp)
    {
        return "";
    }

    std::string out = "";
    while (true)
    {
        int rc = fread(buf, 1, sizeof(buf), fp);
        if (rc <= 0)
        {
            break;
        }

        out.append(buf, rc);
    }

    pclose(fp);

    return out;
}


int ReadFileData(const std::string& file, std::vector<char>& data)
{
    size_t fileSize = GetFileSize(file.data());
    if (fileSize <= 0)
    {
        return -1;
    }

    FILE* fp = fopen(file.data(), "r");
    if (NULL == fp)
    {
        return -1;
    }

    data.resize(fileSize);

    size_t rc = fread(&data[0], 1, fileSize, fp);

    fclose(fp);

    if (rc != fileSize)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int WriteFileData(const std::string& file, const void* data, size_t dataSize)
{
    FILE* fp = fopen(file.data(), "w");
    if (NULL == fp)
    {
        return -1;
    }

    size_t rc = fwrite(data, 1, dataSize, fp);

    fclose(fp);

    if (rc != dataSize)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


bool IsIntranetIp(in_addr_t ip)
{
    /*
        10.0.0.0/8:         10.0.0.0 - 10.255.255.255
        172.16.0.0/12:      172.16.0.0 - 172.31.255.255
        192.168.0.0/16:     192.168.0.0 - 192.168.255.255
    */

    in_addr_t ip_local = ntohl(ip);

    if (0x0A000000 == (ip_local & 0xFF000000))
    {
        return true;
    }

    if (0xAC100000 == (ip_local & 0xFFF00000))
    {
        return true;
    }

    if (0xC0A80000 == (ip_local & 0xFFFF0000))
    {
        return true;
    }

    return false;
}

