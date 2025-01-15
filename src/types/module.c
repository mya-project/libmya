#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "types/token.h"

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

token_t*
module_add_token(module_t* module)
{
  if (module->_tokens_length >= module->tokens_count) {
    module->_tokens_length += MODULE_TOKENS_LENGTH_INCREMENT;
    module->tokens = realloc(module->tokens, sizeof(token_t) * module->_tokens_length);
  }

  return &module->tokens[module->tokens_count++];
}
