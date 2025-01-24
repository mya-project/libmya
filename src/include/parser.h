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
 * Parse a bitfield statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement_bitfield(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a register statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement_register(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a inst statement adding it as a children on `parent` AST node.
 *
 * @param module  The module where the AST is.
 * @param parent  The AST node parent for the statement.
 * @param token   The token where to start parsing the statement.
 *
 * @return  The number of tokens used on the statement.
 */
unsigned int
parse_statement_inst(module_t* module, ast_node_t* parent, token_t* token);

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


/**
 * Parse a size specification in the format `[ EXPRESSION ]` adding it as a children on `parent` AST node.
 *
 * @param module   The module where the AST is.
 * @param parent   The AST node parent for the size specification.
 * @param token    The token where to start parsing the size specification.
 * @param example  A code example printed on error messages when the size spec is syntactically wrong.
 *
 * @return  The number of tokens used on the size specification.
 */
unsigned int
parse_size_spec(module_t* module, ast_node_t* parent, token_t* token, const char* example);

/**
 * Parse a bitfield specification in the format `Bitfield { FIELD_LIST }` or `Bitfield { EXPRESSION }` adding it as a
 * children on `parent` AST node.
 *
 * @param module   The module where the AST is.
 * @param parent   The AST node parent for the bitfield specification.
 * @param token    The token where to start parsing the bitfield specification.
 *
 * @return  The number of tokens used on the bitfield specification.
 */
unsigned int
parse_bitfield_spec(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Parse a field list specification in the format `field = EXPRESSION, ...` adding it as a children on `parent` AST
 * node.
 *
 * @param module   The module where the AST is.
 * @param parent   The AST node parent for the field list specification.
 * @param token    The token where to start parsing the field list specification. It should be the open braces (`{`).
 *
 * @return  The number of tokens used on the field list specification.
 */
unsigned int
parse_fieldlist_spec(module_t* module, ast_node_t* parent, token_t* token);

/**
 * Finds the next token TK_EOF or any of the specified types and then returns the number of tokens traveled.
 *
 * This function could be used to skip wrong tokens when a error as found on parsing a statement. So it's avoid a lot of
 * useless error messages.
 *
 * @param token   Pointer for the first token where to start searching.
 * @param types   Array of token types to search.
 * @param ntypes  Size of `types` array.
 */
unsigned int
parse_advance(token_t* token, token_type_t* types, size_t ntypes);
