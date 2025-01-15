#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module.h"
#include "queue.h"
#include "types/token.h"

static inline void
_module_fill_queue(module_t* module);

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

  cqueue_init(&module->_queue, MODULE_MAX_QUEUE_LENGTH);

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

error_code_t
module_getc(module_t* module, int* chret)
{
  _module_fill_queue(module);

  return cqueue_get(&module->_queue, chret);
}

error_code_t
module_lookup(module_t* module, int* chret, unsigned int seek)
{
  _module_fill_queue(module);

  return cqueue_lookup(&module->_queue, chret, seek);
}

void
module_close(module_t* module)
{
  fclose(module->file);
  module->file = NULL;

  cqueue_close(&module->_queue);
}

static inline void
_module_fill_queue(module_t* module)
{
  char content[MODULE_MAX_QUEUE_LENGTH];
  size_t size;

  if (module->_queue.length < MODULE_MIN_QUEUE_LENGTH) {
    size = fread(content, 1, MODULE_MAX_QUEUE_LENGTH - module->_queue.length, module->file);

    for (int i = 0, ch = 0; i < size && ch != EOF; i++) {
      ch = content[i];

      ERROR_BREAK(cqueue_add(&module->_queue, ch));
    }
  }
}
