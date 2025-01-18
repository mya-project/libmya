#pragma once

#include "types/token.h"

#define AST_INITIAL_CHILDREN_LENGTH   5
#define AST_CHILDREN_LENGTH_INCREMENT 20

typedef struct ast_node
{
  struct ast_node* parent;
  token_t* token;
  struct ast_node* children;
  unsigned int children_count;
  unsigned int _children_length;
} ast_node_t;
