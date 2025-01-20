#include <stdlib.h>
#include <string.h>

#include "ast.h"

static void
_ast_ensure_children_size(ast_node_t* node);

void
ast_node_init(ast_node_t* node, ast_node_t* parent, node_type_t type, token_t* token)
{
  node->parent = parent;
  node->type = type;
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
ast_add_children(ast_node_t* parent, node_type_t type, token_t* token)
{
  _ast_ensure_children_size(parent);

  ast_node_t* child = &parent->children[parent->children_count++];
  ast_node_init(child, parent, type, token);

  return child;
}

ast_node_t*
ast_insert_children(ast_node_t* parent, ast_node_t* child)
{
  _ast_ensure_children_size(parent);

  ast_node_t* new_child = &parent->children[parent->children_count++];

  ast_copy(new_child, child);
  new_child->parent = parent;

  return new_child;
}

void
ast_copy(ast_node_t* destiny, ast_node_t* source)
{
  memcpy(destiny, source, sizeof(ast_node_t));
}

static void
_ast_ensure_children_size(ast_node_t* node)
{
  if (node->children_count < node->_children_length) {
    return;
  }

  node->_children_length += AST_CHILDREN_LENGTH_INCREMENT;
  node->children = realloc(node->children, sizeof(ast_node_t) * node->_children_length);
}
