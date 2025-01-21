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

unsigned int
parse_bitfield_spec(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_BITFIELD_SPEC, token);
  token_t* tkid = token;
  token_t* tkopen_braces = token + 1;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected a bitfield identifier here. Example: Reg{1}"
    );

    return 1;
  }

  if (tkopen_braces->type != TK_OPEN_BRACES) {
    module_add_error(
      module,
      tkopen_braces->line,
      tkopen_braces->column,
      tkopen_braces->lexeme.length,
      "Expected a open braces after bitfield name. Examples:\n"
      "    Reg{1}\n"
      "\n"
      "    Opcode {\n"
      "        opcode = 0x01,\n"
      "        reg = Reg{arg1}\n"
      "    }"
    );

    return 2;
  }

  unsigned int ntokens = 1 + parse_fieldlist_spec(module, node_statement, tkopen_braces);

  token_t* tkclose_braces = token + ntokens;
  if (tkclose_braces->type != TK_CLOSE_BRACES) {
    module_add_error(
      module,
      tkclose_braces->line,
      tkclose_braces->column,
      tkclose_braces->lexeme.length,
      "Expected a close braces at end of field specification list. Examples:\n"
      "    Reg{1}\n"
      "\n"
      "    Opcode {\n"
      "        opcode = 0x01,\n"
      "        reg = Reg{arg1},\n"
      "    }"
    );
  }

  return ntokens + 1;
}

unsigned int
parse_fieldlist_spec(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_FIELD_SPEC, token);
  unsigned int ntokens = 0;

  do {
    ntokens++;
    ntokens += parse_expression(module, node_statement, &token[ntokens]) - 1;
  } while (token[ntokens].type == TK_COMMA);

  return ntokens;
}
