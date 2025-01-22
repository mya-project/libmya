#include "ast.h"
#include "module.h"
#include "parser.h"
#include "types/keywords.h"

unsigned int
_parse_inst_args(module_t* module, ast_node_t* parent, token_t* token);

unsigned int
_parse_arg_spec(module_t* module, ast_node_t* parent, token_t* token);

unsigned int
parse_statement_inst(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_STATEMENT, token);
  token_t* tkid = token + 1;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected an identifier here. Example: inst mov[16](arg1: register[32], arg2: immediate[8]) { ... }"
    );

    return 1;
  }

  ast_add_children(node_statement, NT_IDENTIFIER, tkid);
  unsigned int ntokens =
    2 +
    parse_size_spec(module, node_statement, token + 2, "inst mov[16](arg1: register[32], arg2: immediate[8]) { ... }");

  token_t* tkopen_parens = token + ntokens;

  if (tkopen_parens->type != TK_OPEN_PARENS) {
    module_add_error(
      module,
      tkopen_parens->line,
      tkopen_parens->column,
      tkopen_parens->lexeme.length,
      "Expected a list of arguments for the instruction inside parentheses. Example: inst mov[16](arg1: register[32], "
      "arg2: immediate[8]) { ... }"
    );

    return ntokens + 1;
  }

  ntokens += _parse_inst_args(module, node_statement, tkopen_parens);
  ntokens += parse_fieldlist_spec(module, node_statement, token + ntokens);

  return ntokens;
}

unsigned int
_parse_inst_args(module_t* module, ast_node_t* parent, token_t* token)
{
  ast_node_t* node_statement = ast_add_children(parent, NT_ARG_LIST, token);
  unsigned int ntokens = 1;
  token_t* current;

  for (;;) {
    current = &token[ntokens];

    switch (current->type) {
    case TK_IDENTIFIER:
      ntokens += _parse_arg_spec(module, node_statement, current);
      break;
    case TK_COMMA:
      ntokens++;
      break;
    case TK_CLOSE_PARENS:
      ntokens++;
      goto finish;
    default:
      module_add_error(
        module,
        current->line,
        current->column,
        current->lexeme.length,
        "Unexpected token here. It should follow the syntax like in example: inst mov[16](arg1: register[32], arg2: "
        "immediate[8]) { ... }"
      );

      ntokens++;
      goto finish;
    }
  }

finish:
  return ntokens;
}

unsigned int
_parse_arg_spec(module_t* module, ast_node_t* parent, token_t* token)
{
  token_t* tkid = token;
  token_t* tkcolon = token + 1;
  token_t* tkkeyword = token + 2;

  if (tkid->type != TK_IDENTIFIER) {
    module_add_error(
      module,
      tkid->line,
      tkid->column,
      tkid->lexeme.length,
      "Expected an argument identifier here. Example: inst mov[16](arg1: register[32], arg2: immediate[8]) { ... }"
    );

    return 1;
  }

  if (tkcolon->type != TK_COLON) {
    module_add_error(
      module,
      tkcolon->line,
      tkcolon->column,
      tkcolon->lexeme.length,
      "Expected an colon after argument identifier. Example: inst mov[16](arg1: register[32], arg2: immediate[8]) { "
      "... }"
    );

    return 2;
  }

  if (tkkeyword->type != TK_KEYWORD || (tkkeyword->value != KEY_REGISTER && tkkeyword->value != KEY_IMMEDIATE)) {
    module_add_error(
      module,
      tkkeyword->line,
      tkkeyword->column,
      tkkeyword->lexeme.length,
      "Expected an argument type keyword here. Example: inst mov[16](arg1: register[32], arg2: immediate[8]) { ... }"
    );

    return 3;
  }

  ast_node_t* node_statement = ast_add_children(parent, NT_ARG, token);
  ast_add_children(node_statement, NT_TYPE, tkkeyword);

  return 3 + parse_size_spec(
               module,
               node_statement,
               tkkeyword + 1,
               "inst mov[16](arg1: register[32], arg2: immediate[8]) { ... }"
             );
}
