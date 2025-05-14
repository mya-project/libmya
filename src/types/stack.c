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

  stack->values = malloc(sizeof(token_t*) * STACK_INITIAL_LENGTH);
  stack->_size = STACK_INITIAL_LENGTH;
}

void
stack_close(stack_t* stack)
{
  free(stack->values);
  stack->values = NULL;
}

void
stack_push(stack_t* stack, token_t* token)
{
  _stack_ensure_size(stack);

  stack->values[stack->length++] = token;
}

token_t*
stack_pop(stack_t* stack)
{
  if (stack_isempty(stack)) {
    return NULL;
  }

  return stack->values[--stack->length];
}

token_t*
stack_peek(stack_t* stack)
{
  if (stack_isempty(stack)) {
    return NULL;
  }

  return stack->values[stack->length - 1];
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
  stack->values = realloc(stack->values, sizeof(token_t*) * stack->_size);
}
