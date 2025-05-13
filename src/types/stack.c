#include <stdlib.h>

#include "ast.h"
#include "stack.h"
#include "types/err.h"

void
_stack_ensure_size(stack_t* stack);

void
stack_init(stack_t* stack)
{
  stack->length = 0;

  stack->values = malloc(sizeof(ast_node_t) * STACK_INITIAL_LENGTH);
  stack->_size = STACK_INITIAL_LENGTH;
}

void
stack_close(stack_t* stack)
{
  free(stack->values);
  stack->values = NULL;
}

ast_node_t*
stack_push(stack_t* stack, node_type_t type, token_t* token)
{
  _stack_ensure_size(stack);

  ast_node_init(&stack->values[stack->length], NULL, type, token);

  return &stack->values[stack->length++];
}

ast_node_t*
stack_insert(stack_t* stack, ast_node_t* source)
{
  _stack_ensure_size(stack);

  ast_copy(&stack->values[stack->length], source);

  return &stack->values[stack->length++];
}

error_code_t
stack_pop(stack_t* stack, ast_node_t* value)
{
  if (stack_isempty(stack)) {
    return ERR_EMPTY;
  }

  ast_copy(value, &stack->values[--stack->length]);

  return ERR_OK;
}

ast_node_t*
stack_peek(stack_t* stack)
{
  if (stack_isempty(stack)) {
    return NULL;
  }

  return &stack->values[stack->length - 1];
}

bool
stack_isempty(stack_t* stack)
{
  return stack->length == 0;
}

void
_stack_ensure_size(stack_t* stack)
{
  if (stack->length < stack->_size) {
    return;
  }

  stack->_size += STACK_LENGTH_INCREMENT;
  stack->values = realloc(stack->values, sizeof(ast_node_t) * stack->_size);
}
