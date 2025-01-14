#include <stdlib.h>
#include <string.h>

#include "module.h"

error_code_t
module_init(module_t* module, const char* filepath)
{
  module->file = fopen(filepath, "r");

  if (! module->file) {
    return ERR_FILE_NOT_FOUND;
  }

  strncpy(module->filepath, filepath, MODULE_MAX_FILEPATH_SIZE);
  module->filepath[MODULE_MAX_FILEPATH_SIZE] = '\0';

  module->tokens = malloc(sizeof(token_t) * MODULE_INITIAL_TOKENS_LENGTH);
  module->tokens_count = 0;
  module->_tokens_length = MODULE_INITIAL_TOKENS_LENGTH;

  return ERR_OK;
}
