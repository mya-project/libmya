#include "ast.h"
#include "module.h"
#include "parser.h"

unsigned int
parse_statement_set(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_STATEMENT, token);
  token_t* tkid = token + 1;
  token_t* tkequal = token + 2;
  token_t* tkexpr = token + 3;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected an identifier here. Example: set NAME = value;"
    );

    return 1;
  }

  if (tkequal->type != TK_EQUAL) {
    module_add_error(
      module,
      tkequal->line,
      tkequal->column,
      tkequal->lexeme.length,
      "Expected an equal operator here. Example: set NAME = value;"
    );
  }

  ast_add_children(node_statement, NT_IDENTIFIER, tkid);

  unsigned int ntokens = 3 + parse_expression(module, node_statement, tkexpr);

  token_t* tksemicolon = token + ntokens;

  if (tksemicolon->type != TK_SEMICOLON) {
    module_add_error(
      module,
      tksemicolon->line,
      tksemicolon->column,
      1,
      "Expected semicolon at end of the set command. Example: set NUMBER = 1;"
    );
  }

  return ntokens + 1;
}
