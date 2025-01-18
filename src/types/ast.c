#include <stdlib.h>

#include "ast.h"

void
ast_node_init(ast_node_t* node, ast_node_t* parent, token_t* token)
{
  node->parent = parent;
  node->token = token;

  node->children = malloc(sizeof(ast_node_t) * AST_INITIAL_CHILDREN_LENGTH);
  node->children_count = 0;
  node->_children_length = AST_INITIAL_CHILDREN_LENGTH;
}

void
ast_close(ast_node_t* root)
{
  for (int i = 0; i < root->children_count; i++) {
    ast_close(&root->children[i]);
  }

  free(root->children);
  root->children = NULL;
}

ast_node_t*
ast_add_children(ast_node_t* node, token_t* token)
{
  if (node->children_count >= node->_children_length) {
    node->_children_length += AST_CHILDREN_LENGTH_INCREMENT;
    node->children = realloc(node->children, sizeof(ast_node_t) * node->_children_length);
  }

  ast_node_t* child = &node->children[node->children_count++];
  ast_node_init(child, node, token);

  return child;
}
