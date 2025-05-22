#include "evaluator.h"
#include "mir.h"
#include "module.h"
#include "types/keywords.h"

void
eval_register(mir_t* mir, module_t* module, ast_node_t* ast)
{
  if (ast->type != NT_STATEMENT || ast->token->value != KEY_REGISTER) {
    module_add_error(
      module,
      ast->token->line,
      ast->token->column,
      ast->token->lexeme.length,
      "Unexpected token where is expected a register statement."
    );

    return;
  }

  ast_node_t* node_name = &ast->children[0];
  ast_node_t* node_size = &ast->children[1];
  ast_node_t* node_spec = &ast->children[2];

  int64_t size = eval_expression(&mir->variables, module, node_size);
  if (size < 0 || size > 4096) {
    module_add_error(
      module,
      node_size->token->line,
      node_size->token->column,
      node_size->token->lexeme.length,
      "Register size should be between 0 and 4096."
    );

    return;
  }

  mir_register_t* reg = mir_add_register(mir, node_name->token->lexeme.data, size);
  eval_bitfield_spec(&reg->spec, module, node_spec, &mir->variables);
}
