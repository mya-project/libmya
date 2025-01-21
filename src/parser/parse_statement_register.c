#include "ast.h"
#include "module.h"
#include "parser.h"

unsigned int
parse_statement_register(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_STATEMENT, token);
  token_t* tkid = token + 1;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected an identifier here. Example: register r1[32] = Reg{1}"
    );

    return 1;
  }

  ast_add_children(node_statement, NT_IDENTIFIER, tkid);
  unsigned int ntokens = 2 + parse_size_spec(module, node_statement, token + 2, "register r1[32] = Reg{1}");

  token_t* tkequal = token + ntokens;

  if (tkequal->type != TK_EQUAL) {
    module_add_error(
      module,
      tkequal->line,
      tkequal->column,
      tkequal->lexeme.length,
      "Expected an equal symbol here. Example: register r1[32] = Reg{1}"
    );

    return ntokens + 1;
  }

  return ntokens + 1 + parse_bitfield_spec(module, node_statement, tkequal + 1);
}
