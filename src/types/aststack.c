#include <stdlib.h>

#include "ast.h"
#include "aststack.h"
#include "types/err.h"

void
_stack_ensure_size(aststack_t* stack);

void
aststack_init(aststack_t* stack)
{
  stack->length = 0;

  stack->values = malloc(sizeof(ast_node_t) * ASTSTACK_INITIAL_LENGTH);
  stack->_size = ASTSTACK_INITIAL_LENGTH;
}

void
aststack_close(aststack_t* stack)
{
  free(stack->values);
  stack->values = NULL;
}

ast_node_t*
aststack_push(aststack_t* stack, node_type_t type, token_t* token)
{
  _stack_ensure_size(stack);

  ast_node_init(&stack->values[stack->length], NULL, type, token);

  return &stack->values[stack->length++];
}

ast_node_t*
aststack_insert(aststack_t* stack, ast_node_t* source)
{
  _stack_ensure_size(stack);

  ast_copy(&stack->values[stack->length], source);

  return &stack->values[stack->length++];
}

error_code_t
aststack_pop(aststack_t* stack, ast_node_t* value)
{
  if (aststack_isempty(stack)) {
    return ERR_EMPTY;
  }

  ast_copy(value, &stack->values[--stack->length]);

  return ERR_OK;
}

bool
aststack_isempty(aststack_t* stack)
{
  return stack->length == 0;
}

void
_stack_ensure_size(aststack_t* stack)
{
  if (stack->length < stack->_size) {
    return;
  }

  stack->_size += ASTSTACK_LENGTH_INCREMENT;
  stack->values = realloc(stack->values, sizeof(ast_node_t) * stack->_size);
}
