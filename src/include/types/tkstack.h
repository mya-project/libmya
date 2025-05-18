#pragma once

#include "types/token.h"

#define TKSTACK_INITIAL_LENGTH   20
#define TKSTACK_LENGTH_INCREMENT 50

/**
 * A struct representing a dynamic stack of `token_t` pointers.
 */
typedef struct tkstack
{
  token_t** values;     ///< Array of values on the stack.
  unsigned int length;  ///< Number of elements on the stack.
  unsigned int _size;   ///< Current number of elements that fits on the stack.
} tkstack_t;
