#include <stdlib.h>

#include "stack.h"
#include "types/err.h"

void
stack_init(stack_t* stack)
{
  stack->length = 0;

  stack->values = malloc(sizeof(void*) * STACK_INITIAL_LENGTH);
  stack->_size = STACK_INITIAL_LENGTH;
}

unsigned int
stack_push(stack_t* stack, void* value)
{
  if (stack->length >= stack->_size) {
    stack->_size += STACK_LENGTH_INCREMENT;
    stack->values = realloc(stack->values, sizeof(void*) * stack->_size);
  }

  stack->values[stack->length] = value;

  return stack->length++;
}

error_code_t
stack_pop(stack_t* stack, void** value)
{
  if (stack_isempty(stack)) {
    return ERR_EMPTY;
  }

  *value = stack->values[--stack->length];

  return ERR_OK;
}

bool
stack_isempty(stack_t* stack)
{
  return stack->length == 0;
}
