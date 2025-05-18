#include <stdlib.h>

#include "ast.h"
#include "tkstack.h"
#include "types/err.h"

void
_tkstack_ensure_size(tkstack_t* stack);

void
tkstack_init(tkstack_t* stack)
{
  stack->length = 0;

  stack->values = malloc(sizeof(token_t*) * TKSTACK_INITIAL_LENGTH);
  stack->_size = TKSTACK_INITIAL_LENGTH;
}

void
tkstack_close(tkstack_t* stack)
{
  free(stack->values);
  stack->values = NULL;
}

void
tkstack_push(tkstack_t* stack, token_t* token)
{
  _tkstack_ensure_size(stack);

  stack->values[stack->length++] = token;
}

token_t*
tkstack_pop(tkstack_t* stack)
{
  if (tkstack_isempty(stack)) {
    return NULL;
  }

  return stack->values[--stack->length];
}

token_t*
tkstack_peek(tkstack_t* stack)
{
  if (tkstack_isempty(stack)) {
    return NULL;
  }

  return stack->values[stack->length - 1];
}

bool
tkstack_isempty(tkstack_t* stack)
{
  return stack->length == 0;
}

void
_tkstack_ensure_size(tkstack_t* stack)
{
  if (stack->length < stack->_size) {
    return;
  }

  stack->_size += TKSTACK_LENGTH_INCREMENT;
  stack->values = realloc(stack->values, sizeof(token_t*) * stack->_size);
}
