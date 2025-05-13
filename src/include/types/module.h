#pragma once

#include <stdio.h>

#include "types/ast.h"
#include "types/cqueue.h"
#include "types/dstring.h"
#include "types/token.h"

#define MODULE_MAX_FILEPATH_SIZE       127
#define MODULE_INITIAL_ERRORS_LENGTH   5
#define MODULE_INITIAL_TOKENS_LENGTH   100
#define MODULE_ERRORS_LENGTH_INCREMENT 10
#define MODULE_TOKENS_LENGTH_INCREMENT 50
#define MODULE_MAX_QUEUE_LENGTH        100
#define MODULE_MIN_QUEUE_LENGTH        20

/**
 * Struct that represents a error inside a Mya module.
 */
typedef struct module_error
{
  unsigned int line;    ///< The module's line where the error is.
  unsigned int column;  ///< The line's column where the error starts.
  unsigned int length;  ///< The length of the part where has an error in the line. It's starts on `column` and ends on
                        ///< `column + length`.
  dstring_t message;    ///< The error message to print.
} module_error_t;

/**
 * Struct that represents a Mya module.
 */
typedef struct module
{
  FILE* file;                                   ///< Module's file handler.
  token_t* tokens;                              ///< List of tokens inside the module.
  ast_node_t ast;                               ///< AST of the module.
  module_error_t* errors;                       ///< List of errors inside the module.
  unsigned int tokens_count;                    ///< Number of tokens on `tokens` list.
  unsigned int _tokens_length;                  ///< Internal field with the size of `tokens` allocated memory.
  unsigned int errors_count;                    ///< Number of errors on `errors` list.
  unsigned int _errors_length;                  ///< Internal field with the size of `errors` allocated memory.
  cqueue_t _queue;                              ///< Internal queue to read file character by character.
  char filepath[MODULE_MAX_FILEPATH_SIZE + 1];  ///< Module's filepath.
} module_t;
