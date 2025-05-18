#pragma once

#include "ast.h"

#define ASTSTACK_INITIAL_LENGTH   20
#define ASTSTACK_LENGTH_INCREMENT 50

/**
 * A struct representing a dynamic stack. Each value on the stack is a `ast_node_t` struct.
 */
typedef struct stack
{
  ast_node_t* values;   ///< Array of values on the stack.
  unsigned int length;  ///< Number of elements on the stack.
  unsigned int _size;   ///< Current number of elements that fits on the stack.
} aststack_t;
