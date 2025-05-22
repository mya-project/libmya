#include <ctype.h>

#include "evaluator.h"
#include "mir.h"
#include "module.h"
#include "types/keywords.h"

void
eval_bitfield(mir_t* mir, module_t* module, ast_node_t* ast)
{
  if (ast->type != NT_STATEMENT || ast->token->value != KEY_BITFIELD) {
    module_add_error(
      module,
      ast->token->line,
      ast->token->column,
      ast->token->lexeme.length,
      "Unexpected token where is expected a bitfield statement."
    );

    return;
  }

  ast_node_t* node_name = &ast->children[0];
  ast_node_t* node_size = &ast->children[1];

  int64_t size = eval_expression(&mir->variables, module, node_size);
  if (size < 0 || size > 512) {
    module_add_error(
      module,
      node_size->token->line,
      node_size->token->column,
      node_size->token->lexeme.length,
      "Bitfield size should be between 0 and 512."
    );

    return;
  }

  const char* name = node_name->token->lexeme.data;
  if (! isupper(name[0])) {
    module_add_error(
      module,
      node_name->token->line,
      node_name->token->column,
      node_name->token->lexeme.length,
      "Bitfield name should start with upper case."
    );

    return;
  }

  mir_bitfield_t* bitfield = mir_add_bitfield(mir, name, size);
  if (ast->children_count != 3) {
    return;
  }

  ast_node_t* node_body = &ast->children[2];
  if (node_body->type != NT_BITFIELD_BODY) {
    module_add_error(
      module,
      node_body->token->line,
      node_body->token->column,
      node_body->token->lexeme.length,
      "Bitfield body declaration expected here."
    );

    return;
  }

  int64_t total_size = 0;

  for (int i = 0; i < node_body->children_count; i++) {
    ast_node_t* field = &node_body->children[i];
    const char* field_name = field->token->lexeme.data;
    int64_t field_size = eval_expression(&mir->variables, module, field->children);

    mir_bitfield_add_field(bitfield, field_name, field_size);

    total_size += field_size;
  }

  if (size != total_size) {
    module_add_error(
      module,
      node_size->token->line,
      node_size->token->column,
      node_size->token->lexeme.length,
      "Bitfield size should be equal to the sum of all field sizes."
    );
  }
}
