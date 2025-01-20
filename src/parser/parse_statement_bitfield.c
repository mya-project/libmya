#include "ast.h"
#include "module.h"
#include "parser.h"

static unsigned int
_parse_bitfield_body(module_t* module, ast_node_t* parent, token_t* token);

unsigned int
parse_statement_bitfield(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_STATEMENT, token);
  token_t* tkid = token + 1;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected an identifier here. Example: bitfield Name[4]"
    );

    return 1;
  }

  ast_add_children(node_statement, NT_IDENTIFIER, tkid);
  unsigned int ntokens = 2 + parse_size_spec(module, node_statement, token + 2, "bitfield Name[4]");

  token_t* tkopen_braces = token + ntokens;

  if (tkopen_braces->type == TK_OPEN_BRACES) {
    ast_node_t* body = ast_add_children(node_statement, NT_BITFIELD_BODY, tkopen_braces);
    ntokens += 1 + _parse_bitfield_body(module, body, tkopen_braces + 1);
  }

  return ntokens;
}

static unsigned int
_parse_bitfield_body(module_t* module, ast_node_t* parent, token_t* token)
{
  unsigned int ntokens = 0;
  token_t* current;
  ast_node_t* field;

  for (;;) {
    current = &token[ntokens];

    switch (current->type) {
    case TK_IDENTIFIER:
      field = ast_add_children(parent, NT_FIELD, current);

      ntokens += 1 + parse_size_spec(module, field, current + 1, "opcode[5]");
      break;
    case TK_CLOSE_BRACES:
      return ntokens + 1;
    default:
      module_add_error(
        module,
        current->line,
        current->column,
        current->lexeme.length,
        "Unexpected token inside a bitfield body. It should only have field lists with size specification. Example:\n"
        "    bitfield Opcode[4] {\n"
        "        opcode[5]\n"
        "        reg[3]\n"
        "    }"
      );

      ntokens++;
      break;
    }
  }

  return ntokens;
}
