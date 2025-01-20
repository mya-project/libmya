#include "ast.h"
#include "module.h"
#include "parser.h"
#include "types/keywords.h"

unsigned int
parse_size_spec(module_t* module, ast_node_t* parent, token_t* token, const char* example)
{
  char message[128];
  token_t* tkopen_bracket = token;
  token_t* tkexpr = token + 1;

  if (tkopen_bracket->type != TK_OPEN_BRACKET) {
    snprintf(
      message,
      sizeof message - 1,
      "Expected a size specifier after the %s name. Example: %s",
      mya_keywords[token->value],
      example
    );

    module_add_error(module, tkopen_bracket->line, tkopen_bracket->column, tkopen_bracket->lexeme.length, message);

    return 2;
  }

  unsigned int ntokens = parse_expression(module, parent, tkexpr);

  token_t* tkclose_bracket = token + ntokens;

  if (tkclose_bracket->type != TK_CLOSE_BRACKET) {
    snprintf(message, sizeof message - 1, "Expected a close bracket here. Example: %s", example);

    module_add_error(
      module,
      tkclose_bracket->line,
      tkclose_bracket->column,
      tkclose_bracket->lexeme.length,
      "Expected a close bracket here. Example: bitfield Name[4]"
    );
  }

  return ntokens + 1;
}
