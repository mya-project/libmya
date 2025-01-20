#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "debug.h"
#include "dstring.h"
#include "error_handling.h"
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

  ast_node_init(&module->ast, NULL, NT_ROOT, NULL);

  module->tokens = malloc(sizeof(token_t) * MODULE_INITIAL_TOKENS_LENGTH);
  module->tokens_count = 0;
  module->_tokens_length = MODULE_INITIAL_TOKENS_LENGTH;

  module->errors = malloc(sizeof(module_error_t) * MODULE_INITIAL_ERRORS_LENGTH);
  module->errors_count = 0;
  module->_errors_length = MODULE_INITIAL_ERRORS_LENGTH;

  cqueue_init(&module->_queue, MODULE_MAX_QUEUE_LENGTH);

  return ERR_OK;
}

token_t*
module_add_token(module_t* module)
{
  if (module->tokens_count >= module->_tokens_length) {
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

  free(module->tokens);
  module->tokens = NULL;

  cqueue_close(&module->_queue);

  for (int i = 0; i < module->errors_count; i++) {
    dstring_close(&module->errors[i].message);
  }

  free(module->errors);
  module->errors = NULL;

  ast_close(&module->ast);
}

void
module_add_error(module_t* module, unsigned int line, unsigned int column, unsigned int length, const char* message)
{
  if (module->errors_count >= module->_errors_length) {
    module->_errors_length += MODULE_ERRORS_LENGTH_INCREMENT;
    module->errors = realloc(module->errors, sizeof(module_error_t) * module->_errors_length);
  }

  module_error_t* error = &module->errors[module->errors_count++];

  error->line = line;
  error->column = column;
  error->length = length;

  dstring_init(&error->message, 100);
  dstring_copy(&error->message, message);

  DPRINTF1("Error at %s:%d:%d -> %s\n", module->filepath, line, column, message);
}

void
module_print_errors(module_t* module)
{
  module_error_t* error;

  for (int i = 0; i < module->errors_count; i++) {
    error = &module->errors[i];

    error_module_ctx(module, error->line, error->column, error->length, error->message.data);
    fputc('\n', stderr);
  }
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
