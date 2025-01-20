#pragma once

#include "colors.h"

#define ERR_CTX_SIZE      3
#define ERR_CTX_LINE_WRAP 80

#define ERR_PREFIX C_RED "Error" C_NORMAL ": "

/**
 * Enumeration of error codes.
 */
typedef enum error_code
{
  ERR_OK = 0,
  ERR_EMPTY,
  ERR_FILE_NOT_FOUND,
  ERR_INVALID_CODE,
  ERR_INVALID_INDEX,
  ERR_MAX_SIZE_EXCEEDED,
} error_code_t;

#define ERROR_IF(expr, then)                                                                                           \
  {                                                                                                                    \
    error_code_t _err;                                                                                                 \
    if ((_err = (expr)) != ERR_OK) {                                                                                   \
      then;                                                                                                            \
    }                                                                                                                  \
  }

#define ERROR_RET(expr)   ERROR_IF(expr, return _err)
#define ERROR_BREAK(expr) ERROR_IF(expr, break)
