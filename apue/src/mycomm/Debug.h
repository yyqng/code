#pragma once

#ifdef _PKTSPY_DEBUG_

#include <cstdio>

#define DebugPrint(fmt, ...)    fprintf(stderr, fmt, ##__VA_ARGS__)

#else

#define DebugPrint(fmt, ...)

#endif
