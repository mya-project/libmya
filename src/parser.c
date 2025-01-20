#include <stdlib.h>

#include "ast.h"
#include "mya.h"
#include "parser.h"
#include "types/token.h"

error_code_t
mya_parser(module_t* module)
{
  token_t* token;

  for (unsigned int tk_index = 0; tk_index < module->tokens_count; tk_index++) {
    token = &module->tokens[tk_index];

    switch (token->type) {
    case TK_KEYWORD:
      tk_index += parse_statement(module, &module->ast, token) - 1;
      break;
    default:
      return ERR_EMPTY;
    }
  }

  return ERR_OK;
}
