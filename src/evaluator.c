#include "evaluator.h"
#include "mya.h"
#include "types/keywords.h"

error_code_t
mya_evaluator(mir_t* mir, module_t* module)
{
  ast_node_t* current;

  for (int i = 0; i < module->ast.children_count; i++) {
    current = &module->ast.children[i];

    switch (current->token->value) {
    case KEY_INCLUDE:
      break;
    case KEY_SET:
      break;
    case KEY_BITFIELD:
      eval_bitfield(mir, module, current);
      break;
    case KEY_REGISTER:
      eval_register(mir, module, current);
      break;
    case KEY_INST:
      break;
    default:
      module_add_error(
        module,
        current->token->line,
        current->token->column,
        current->token->lexeme.length,
        "It's an invalid statement keyword. Are you sure it's a valid command or declaration?"
      );

      return ERR_INVALID_CODE;
    }
  }
  return ERR_OK;
}
