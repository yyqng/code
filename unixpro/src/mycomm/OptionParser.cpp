#include <libgen.h>

#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "OptionParser.h"

// global help option
Option<bool> g_optHelp("help", false, "--help", "print this help information");

/**
 * @brief 单个选项解析函数，目前只支持“--option=value”这一种形式的选项解析
 *
 * @param opt 选项字符串
 * @param name 选项名输出
 * @param value 选项值输出
 *
 * @return 解析成功时返回true，失败时返回false
 */
bool parse_single_option(const char * opt, std::string & name, std::string & value)
{
    assert(opt);

    auto const len = strlen(opt);

    if (len < 3)    // minimum length is 3
    {
        return false;
    }

    if (opt[0] != '-' || opt[1] != '-')
    {
        return false;
    }

    auto const div = strchr(opt, '=');    // find assignment char

    if (!div)
    {
        name.assign(opt + 2);
        value.clear();
    }
    else
    {
        name.assign(opt + 2, div - opt - 2);
        value.assign(div + 1);
    }

    return true;
}

OptionParser & OptionParser::GetInstance(void)
{
    static OptionParser s_inst;
    return s_inst;
}

bool OptionParser::ParseCommandLine(int const argc, char** argv)
{
    if (argc <= 0)
    {
        fprintf(stderr, "\e[1;31mArgument numbers error(argc < 0)\e[0m\n");
        return false;
    }

    m_programName.assign(basename(argv[0]));

    for (auto i = 1; i < argc; ++i)
    {
        std::string name;
        std::string value;

        if (!parse_single_option(argv[i], name, value))
        {
            fprintf(stderr, "\e[1;31mInvalid option %s\e[0m\n", argv[i]);
            return false;
        }

        auto const opt = GetOption(name);

        if (!opt)
        {
            fprintf(stderr, "\e[1;31mInvalid option in cmdline, name='%s'\e[0m\n", argv[i]);
            return false;
        }

        if (!opt->ConvertFromString(value))
        {
            fprintf(stderr, "\e[1;31mInvalid option in cmdline, name='%s', value='%s'\e[0m\n", argv[i], value.c_str());
            return false;
        }
    }

    return true;
}

bool OptionParser::ParseConfigFile(const char * file)
{
    assert(file);

    std::ifstream ifs(file, std::ios::in);

    if (!ifs)
    {
        fprintf(stderr, "\e[1;31mFailed to open config file '%s', err=%m\e[0m\n", file);
        return false;
    }

    size_t line = 0;

    for (char buffer[1024]; ifs.getline(buffer, sizeof buffer); )
    {
        ++line;

        if (buffer[0] == '#' || buffer[0] == '\n' || buffer[0] == '\r' || buffer[0] == '\0' || buffer[0] == ' ') continue;

        auto const end = buffer + strlen(buffer);

        auto p = buffer + 1;
        while (p < end && *p != ' ' && *p != '\t') ++p;
        if (p < end) *p++ = '\0';
        while (p < end && (*p == ' ' || *p == '\t')) ++p;

        auto const name = buffer;
        std::string value;
        value.reserve(strlen(p));

        for (char quot = 0; *p; )
        {
            if (quot == 0 && *p == ' ') break;

            if (*p == '"' || *p == '\'')
            {
                if (quot == 0)
                {
                    quot = *p++;
                }
                else if (quot == *p)
                {
                    quot = 0;
                    ++p;
                }
                else
                    value.append(1, *p);
            }
            else
            {
                value.append(1, *p);
                ++p;
            }
        }

        auto const opt = GetOption(name);

        if (!opt)
        {
            fprintf(stderr, "\e[1;31mInvalid option in configuration, file='%s', line=%ld, name='%s'\e[0m\n", file, line, name);
            return false;
        }

        if (!opt->ConvertFromString(value))
        {
            fprintf(stderr, "\e[1;31mInvalid option in configuration, file='%s', line=%ld, name='%s', value='%s'\e[0m\n", file, line, name, value.c_str());
            return false;
        }
    }

    return true;
}

void OptionParser::PrintHelpInformation(void) const
{
    std::cerr << "USAGE: " << m_programName << " <options>" << std::endl;
    std::cerr << "Available options:" << std::endl;
    std::cerr << "    " << std::setw(26) << std::left << "--help" << "print this help information" << std::endl;

    for (auto itr = m_optionMap.begin(); m_optionMap.end() != itr; ++itr)
    {
        auto & opt = itr->second;
        if (opt != &g_optHelp)
            std::cerr << "    " << std::setw(26) << std::left << opt->Sample() << opt->Description() << std::endl;
    }
}
