#include <stdlib.h>

#include "ast.h"
#include "debug.h"
#include "macro_utils.h"
#include "mya.h"
#include "parser.h"
#include "types/keywords.h"
#include "types/token.h"

error_code_t
mya_parser(module_t* module)
{
  token_t* token;

  for (unsigned int tk_index = 0; tk_index < module->tokens_count;) {
    token = &module->tokens[tk_index];

    switch (token->type) {
    case TK_KEYWORD:
      DPRINTF2(
        "Parsing statement: %s at %s:%d:%d.\n",
        token->lexeme.data,
        module->filepath,
        token->line,
        token->column
      );

      tk_index += parse_statement(module, &module->ast, token);
      tk_index += parse_advance(&module->tokens[tk_index], ARR_TT(TK_KEYWORD));
      break;
    case TK_EOF:
      goto finish;
    default:
      module_add_error(
        module,
        token->line,
        token->column,
        token->lexeme.length,
        "Unexpected token here. It's expected to be a valid statement keyword."
      );

      tk_index++;
      break;
    }
  }

finish:
  return (module->errors_count == 0) ? ERR_OK : ERR_INVALID_CODE;
}
