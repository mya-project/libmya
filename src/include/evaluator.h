#pragma once

#include <stdint.h>

#include "types/ast.h"
#include "types/mir.h"
#include "types/module.h"

/**
 * Evaluates a mathetical expression.
 *
 * @param variables The hashtable with the declared variables.
 * @param module    Mya module where this expression is in.
 * @param ast       The AST node where start the expression.
 */
int64_t
eval_expression(hashtable_t* variables, module_t* module, ast_node_t* ast);
