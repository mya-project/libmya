#pragma once

#include <stdint.h>

#include "types/ast.h"
#include "types/mir.h"
#include "types/module.h"

/**
 * Evaluates a mathetical expression.
 *
 * @param variables  The hashtable with the declared variables.
 * @param module     Mya module where this expression is in.
 * @param ast        The AST node where start the expression.
 */
int64_t
eval_expression(hashtable_t* variables, module_t* module, ast_node_t* ast);

/**
 * Evaluates a bitfield statement.
 *
 * @param mir     The MIR struct where to add the intermediate represetation.
 * @param module  Mya module where the statement is in.
 * @param ast     The AST node where start the statement.
 */
void
eval_bitfield(mir_t* mir, module_t* module, ast_node_t* ast);

/**
 * Evaluates an include statement.
 *
 * @param mir     The MIR struct where to add the intermediate represetation.
 * @param module  Mya module where the statement is in.
 * @param ast     The AST node where start the statement.
 */
void
eval_include(mir_t* mir, module_t* module, ast_node_t* ast);

/**
 * Evaluates an inst statement.
 *
 * @param mir     The MIR struct where to add the intermediate represetation.
 * @param module  Mya module where the statement is in.
 * @param ast     The AST node where start the statement.
 */
void
eval_inst(mir_t* mir, module_t* module, ast_node_t* ast);

/**
 * Evaluates a register statement.
 *
 * @param mir     The MIR struct where to add the intermediate represetation.
 * @param module  Mya module where the statement is in.
 * @param ast     The AST node where start the statement.
 */
void
eval_register(mir_t* mir, module_t* module, ast_node_t* ast);

/**
 * Evaluates a set statement.
 *
 * @param mir     The MIR struct where to add the intermediate represetation.
 * @param module  Mya module where the statement is in.
 * @param ast     The AST node where start the statement.
 */
void
eval_set(mir_t* mir, module_t* module, ast_node_t* ast);

/**
 * Evaluates a bitfield specification expression.
 *
 * @param spec       The spec struct where to save the spec data.
 * @param module     Mya module where the expression is in.
 * @param ast        The AST node where start the bitfield specification.
 * @param variables  The hashtable with the declared variables.
 */
void
eval_bitfield_spec(mir_bitfield_spec_t* spec, module_t* module, ast_node_t* ast, hashtable_t* variables);
