#pragma once

#include "types/err.h"
#include "types/module.h"
#include "types/token.h"

/**
 * Parse a statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a include statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement_include(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a set statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement_set(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a mathematical expression adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the expression.
 * @param token   The token where to start parsing the expression.
 *
 * @return  The number of tokens used on the expression.
 */
unsigned int
parse_expression(module_t* module, ast_node_t* parent, token_t* token);