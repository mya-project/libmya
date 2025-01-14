#pragma once

#include <stdio.h>

#include "types/token.h"

#define MODULE_MAX_FILEPATH_SIZE     127
#define MODULE_INITIAL_TOKENS_LENGTH 100

typedef struct module
{
  FILE* file;
  token_t* tokens;
  unsigned int tokens_count;
  unsigned int _tokens_length;
  char filepath[MODULE_MAX_FILEPATH_SIZE + 1];
} module_t;
