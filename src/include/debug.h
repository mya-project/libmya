#pragma once

#include <stdio.h>

#include "colors.h"

#define DPRINTF(level, fmt, ...) fprintf(stderr, "[" C_BLUE "DEBUG " C_GREEN #level C_NORMAL "] " fmt, __VA_ARGS__)

#if DLEVEL >= 1
#  define DPRINTF1(fmt, ...) DPRINTF(1, fmt, __VA_ARGS__)
#  define DEBUG_IF(expr, code)                                                                                         \
    if (expr) {                                                                                                        \
      code;                                                                                                            \
    }
#else
#  define DPRINTF1(fmt, ...)
#  define DEBUG_IF(expr, code)
#endif

#if DLEVEL >= 2
#  define DPRINTF2(fmt, ...) DPRINTF(2, fmt, __VA_ARGS__)
#else
#  define DPRINTF2(fmt, ...)
#endif

#if DLEVEL >= 3
#  define DPRINTF3(fmt, ...) DPRINTF(3, fmt, __VA_ARGS__)
#else
#  define DPRINTF3(fmt, ...)
#endif
