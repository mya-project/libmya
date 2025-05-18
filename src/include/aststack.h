#pragma once

#include <stdbool.h>

#include "types/aststack.h"
#include "types/err.h"

/**
 * Initializes the given stack.
 *
 * @param stack  The stack to be initialized.
 */
void
aststack_init(aststack_t* stack);

/**
 * Closes the given stack.
 *
 * @param stack  The stack to be closed.
 */
void
aststack_close(aststack_t* stack);

/**
 * Push a new value on the stack.
 *
 * @param stack  The stack where tbe value will be pushed.
 * @param type   The AST node type.
 * @param token  The AST node token.
 *
 * @return  A pointer for the new value inside the stack.
 */
ast_node_t*
aststack_push(aststack_t* stack, node_type_t type, token_t* token);

/**
 * Push a new value on the stack copying from `source` pointer.
 *
 * @param stack   The stack where tbe value will be pushed.
 * @param source  The AST node content.
 *
 * @return  A pointer for the new value inside the stack.
 */
ast_node_t*
aststack_insert(aststack_t* stack, ast_node_t* source);

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
aststack_pop(aststack_t* stack, ast_node_t* value);

/**
 * Check if the given stack is empty.
 *
 * @param stack  The stack to check.
 *
 * @return  true on stack is empty.
 * @return  false if stack has values.
 */
bool
aststack_isempty(aststack_t* stack);
