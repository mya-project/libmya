#pragma once

#include <stdbool.h>

#include "types/err.h"
#include "types/stack.h"

/**
 * Initializes the given stack.
 *
 * @param stack  The stack to be initialized.
 */
void
stack_init(stack_t* stack);

/**
 * Push a new value on the stack.
 *
 * @param stack  The stack where tbe value will be pushed.
 * @param value  The value to push on the stack.
 *
 * @return  The index of the new value inside the stack.
 */
unsigned int
stack_push(stack_t* stack, void* value);

/**
 * Pop a value from the stack.
 *
 * @param stack  The stack from where the value will be poped.
 * @param value  Pointer for where the poped value will be saved.
 *
 * @return  ERR_EMPTY on stack is empty.
 * @return  ERR_OK on value is poped successful.
 */
error_code_t
stack_pop(stack_t* stack, void** value);

/**
 * Check if the given stack is empty.
 *
 * @param stack  The stack to check.
 *
 * @return  true on stack is empty.
 * @return  false if stack has values.
 */
bool
stack_isempty(stack_t* stack);
