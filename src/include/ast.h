#pragma once

#include "types/ast.h"

/**
 * Initializes an AST node.
 *
 * @param node    The node to be initialized.
 * @param parent  Parent node of the given node.
 * @param type    Type of the node.
 * @param token   Token of the given node.
 */
void
ast_node_init(ast_node_t* node, ast_node_t* parent, node_type_t type, token_t* token);

/**
 * Closes the given AST root node and all children.
 *
 * @param root  The AST's root node.
 */
void
ast_close(ast_node_t* root);

/**
 * Add a new children for the given AST node.
 *
 * @param node   The node where the new children will be added.
 * @param type   Type of the node.
 * @param token  Token to set for the new children node.
 */
ast_node_t*
ast_add_children(ast_node_t* node, node_type_t type, token_t* token);
