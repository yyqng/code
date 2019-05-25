#pragma once

#include "OptionParser.h"
#include "FileDescriptor.h"

struct ShmFdListConvertor
{
    bool operator()(const std::string & str, std::vector<int> & out) const;
};

// spider server port
extern Option<unsigned short> g_optPort;

// shm object name
extern Option<std::string> g_optShmObjName;

// shm object file descriptor list
extern Option<std::vector<int>, ShmFdListConvertor> g_optShmFdList;

// has pktspymgr?
extern Option<bool> g_optHasPktspyMgr;

// log work directory
extern Option<std::string> g_optLogDir;

// UNIX domain socket path
extern Option<std::string> g_optUnixDomainSocketPath;

// configuration file path
extern Option<std::string> g_optConfig;

// max number of concurrent tasks
extern Option<size_t> g_optMaxConcurrentTaskNumber;

// enable/disable bandwidth metering
extern Option<bool> g_optBandwidthMetering;

// log level mask
extern Option<uint32_t> g_optLogLevelMask;

// max task queue size
extern Option<size_t> g_optMaxTaskQueueSize;