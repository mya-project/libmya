#pragma once

#include <stdio.h>

#include "types/token.h"

#define MODULE_MAX_FILEPATH_SIZE       127
#define MODULE_INITIAL_TOKENS_LENGTH   100
#define MODULE_TOKENS_LENGTH_INCREMENT 50

/**
 * Struct that represents a Mya module.
 */
typedef struct module
{
  FILE* file;                                   ///< Module's file handler.
  token_t* tokens;                              ///< List of tokens inside the module.
  unsigned int tokens_count;                    ///< Number of tokens on `tokens` list.
  unsigned int _tokens_length;                  ///< Internal field with the size of `tokens` alloced memory.
  char filepath[MODULE_MAX_FILEPATH_SIZE + 1];  ///< Module's filepath.
} module_t;
