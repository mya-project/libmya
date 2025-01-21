#include <string.h>

#include "module.h"
#include "parser.h"
#include "types/keywords.h"

unsigned int
parse_statement(module_t* module, ast_node_t* parent, token_t* token)
{
  if (token->type != TK_KEYWORD) {
    module_add_error(
      module,
      token->line,
      token->column,
      token->lexeme.length,
      "This token is unexpected here. It's expected to be a valid statement keyword."
    );

    return 1;
  }

  switch (token->value) {
  case KEY_INCLUDE:
    return parse_statement_include(module, parent, token);
  case KEY_SET:
    return parse_statement_set(module, parent, token);
  case KEY_BITFIELD:
    return parse_statement_bitfield(module, parent, token);
  case KEY_REGISTER:
    return parse_statement_register(module, parent, token);
  default:
    module_add_error(
      module,
      token->line,
      token->column,
      token->lexeme.length,
      "It's an invalid statement keyword. Are you sure it's a valid command or declaration?"
    );

    return 1;
  }
}
