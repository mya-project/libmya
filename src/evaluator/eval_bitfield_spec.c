#include "dstring.h"
#include "evaluator.h"
#include "mir.h"
#include "module.h"

mir_bitfield_spec_type_t
_spec_type(ast_node_t* spec);

void
eval_bitfield_spec(mir_bitfield_spec_t* spec, module_t* module, ast_node_t* ast, hashtable_t* variables)
{
  if (ast->type != NT_BITFIELD_SPEC) {
    module_add_error(
      module,
      ast->token->line,
      ast->token->column,
      ast->token->lexeme.length,
      "Unexpected token where is expected a bitfield specification expression."
    );

    return;
  }

  ast_node_t* field_spec = &ast->children[0];
  if (field_spec->type != NT_FIELD_SPEC) {
    module_add_error(
      module,
      ast->token->line,
      ast->token->column,
      ast->token->lexeme.length,
      "Unexpected token where is expected a bitfield specification's field list or expression."
    );

    return;
  }

  dstring_copy(&spec->name, ast->token->lexeme.data);
  spec->type = _spec_type(ast);

  switch (spec->type) {
  case FT_SPEC:
    mir_bitfield_spec_set_spec(spec, field_spec->children[0].token->lexeme.data, FT_LITERAL);
    eval_bitfield_spec(spec->spec, module, &field_spec->children[0], variables);
    break;
  case FT_LITERAL:
    spec->value = eval_expression(variables, module, field_spec->children);
    break;
  case FT_IDENTIFIER:
    dstring_copy(&spec->identifier, field_spec->children[0].token->lexeme.data);
    break;
  case FT_FIELDS:
    for (int i = 0; i < field_spec->children_count; i++) {
      mir_bitfield_spec_t* field =
        mir_bitfield_spec_add_field(spec, field_spec->children[i].token->lexeme.data, FT_LITERAL);
      eval_bitfield_spec(field, module, &field_spec->children[i], variables);
    }
    break;
  }
}

mir_bitfield_spec_type_t
_spec_type(ast_node_t* spec)
{
  ast_node_t* field_spec = &spec->children[0];

  if (field_spec->children[0].type == NT_BITFIELD_SPEC) {
    return FT_SPEC;
  }

  if (field_spec->children[0].token->type == TK_EQUAL) {
    return FT_FIELDS;
  }

  if (field_spec->children_count == 1 && field_spec->children[0].token->type == TK_IDENTIFIER) {
    return FT_IDENTIFIER;
  }

  return FT_LITERAL;
}
