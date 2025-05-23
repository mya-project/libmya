#pragma once

#include <stdbool.h>

#include "types/err.h"
#include "types/tkstack.h"

/**
 * Initializes the given stack.
 *
 * @param stack  The stack to be initialized.
 */
void
tkstack_init(tkstack_t* stack);

/**
 * Closes the given stack.
 *
 * @param stack  The stack to be closed.
 */
void
tkstack_close(tkstack_t* stack);

/**
 * Push a new value on the stack.
 *
 * @param stack  The stack where tbe value will be pushed.
 * @param token  Pointer to a token to add on the stack.
 */
void
tkstack_push(tkstack_t* stack, token_t* token);

/**
 * Pop a value from the stack.
 *
 * @param stack  The stack from where the value will be poped.
 * @param value  Pointer for where the poped value will be saved.
 *
 * @return       NULL when the queue is empty.
 * @return       Pointer to the item.
 */
token_t*
tkstack_pop(tkstack_t* stack);

/**
 * Peeks the value on top of the stack without removing it.
 *
 * @param stack  The stack to peek into.
 *
 * @return  NULL if stack is empty.
 * @return  Pointer to the top node in the stack.
 */
token_t*
tkstack_peek(tkstack_t* stack);

/**
 * Check if the given stack is empty.
 *
 * @param stack  The stack to check.
 *
 * @return  true on stack is empty.
 * @return  false if stack has values.
 */
bool
tkstack_isempty(tkstack_t* stack);
