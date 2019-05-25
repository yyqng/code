#include "SpiderOptions.h"
#include "ipc_defs.h"

// spider server port
Option<unsigned short>
g_optPort("port",
          7788,
          "--port=[port number]",
          "set spider server port");

// shm object name
Option<std::string>
g_optShmObjName("shmObjName",
                SHM_PARSER_NAME,
                "--shmObjName=[name]",
                "set output shared memory object name");

// shm object file descriptor list
Option<std::vector<int>, ShmFdListConvertor>
g_optShmFdList("shmFdList",
               { },
               "--shmFdList=[fd1,fd2,...]",
               "shm objects file descriptor list created by pktspymgr");

// has pktspymgr?
Option<bool>
g_optHasPktspyMgr("hasPktspyMgr",
                  false,
                  "--hasPktspyMgr",
                  "used by pktspymgr, started by pktspymgr");

// log work directory
Option<std::string>
g_optLogDir("logDir",
            std::string(),
            "--logDir=[log directory]",
            "log directory, default value is current work directory");

// UNIX domain socket path
Option<std::string>
g_optUnixDomainSocketPath("socketPath",
                          UNIX_DOMAIN_PATH,
                          "--socketPath=[path]",
                          "UNIX domain socket path, accept local spider task");

// configuration file path
Option<std::string>
g_optConfig("config",
            std::string(),
            "--config=[path]",
            "configuration file path");

// max number of concurrent tasks
Option<size_t>
g_optMaxConcurrentTaskNumber("maxConcurrentTaskNumber",
                             -1,
                             "--maxConcurrentTaskNumber=[number]",
                             "max number of concurrent tasks");

// enable/disable bandwidth metering
Option<bool>
g_optBandwidthMetering("bandwidthMetering",
                       false,
                       "--bandwidthMetering",
                       "enable/disable bandwidth metering, this option is disabled by default");

// log level mask
Option<uint32_t>
g_optLogLevelMask("logLevelMask",
                  0x0F,
                  "--logLevelMask=[mask]",
                  "log level mask, default value is 0x0F, bit0: DBG, bit1: INF, bits2: WRN, bits3: ERR");

// max task queue size
Option<size_t>
g_optMaxTaskQueueSize("maxTaskQueueSize",
                      -1,
                      "--maxTaskQueueSize=[num]",
                      "max task queue size, default value is -1");


bool ShmFdListConvertor::operator()(const std::string & str, std::vector<int> & out) const
{
    char *end = nullptr;
    auto p = str.c_str();

    std::vector<int> vec;

    while (p < &*str.end())
    {
        auto const fd = strtol(p, &end, 10);
        if (end == p) return false;
        vec.emplace_back(fd);
        p = end + 1;
    }

    out.swap(vec);
    return true;
}
