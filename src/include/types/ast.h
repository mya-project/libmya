#pragma once

#include "types/token.h"

#define AST_INITIAL_CHILDREN_LENGTH   5
#define AST_CHILDREN_LENGTH_INCREMENT 20

typedef enum node_type
{
  NT_ARG_LIST,
  NT_EXPRESSION,
  NT_IDENTIFIER,
  NT_INST_BODY,
  NT_SIZE_SPEC,
  NT_STATEMENT,
  NT_TYPE,
  NT_STRING,
  NT_BITFIELD_BODY,
} node_type_t;

typedef struct ast_node
{
  struct ast_node* parent;
  node_type_t type;
  token_t* token;
  struct ast_node* children;
  unsigned int children_count;
  unsigned int _children_length;
} ast_node_t;
