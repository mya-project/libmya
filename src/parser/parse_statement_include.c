#include "ast.h"
#include "module.h"
#include "parser.h"

unsigned int
parse_statement_include(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_STATEMENT, token);
  token_t* tkstring = token + 1;
  token_t* tksemicolon = token + 2;

  if (tkstring->type != TK_STRING) {
    module_add_error(
      module,
      tkstring->line,
      tkstring->column,
      tkstring->lexeme.length,
      "Expected literal string here. Example: include \"module.mya\";"
    );

    return 1;
  }

  if (tksemicolon->type != TK_SEMICOLON) {
    module_add_error(
      module,
      tkstring->line,
      tkstring->column + tkstring->lexeme.length + 1,
      1,
      "Expected semicolon at end of the include command. Example: include \"module.mya\";"
    );
  }

  ast_add_children(node_statement, NT_STRING, tkstring);

  return 2 + (tksemicolon->type == TK_SEMICOLON);
}
