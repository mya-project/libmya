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
 * @param parent  The node parent where the new children will be added.
 * @param type    Type of the node.
 * @param token   Token to set for the new children node.
 *
 * @return  Pointer for the new children on parent.
 */
ast_node_t*
ast_add_children(ast_node_t* parent, node_type_t type, token_t* token);

/**
 * Insert a exitent AST node as children of the given parent node.
 *
 * It's copies the content of the given `child` for the new children on `parent` node.
 *
 * @param parent  The parent where to insert the child.
 * @param child   The child to insert as parent's children.
 *
 * @return  Pointer for the new children on parent.
 */
ast_node_t*
ast_insert_children(ast_node_t* parent, ast_node_t* child);

/**
 * Copies the content of `source` to `destinty` AST nodes.
 *
 * @param destiny  Where to copy the node data.
 * @param source   The node data that will be copied.
 */
void
ast_copy(ast_node_t* destiny, ast_node_t* source);
