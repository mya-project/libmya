#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "types/token.h"

static void
_ast_to_json_aux(ast_node_t* root, FILE* file, int level);

static void
_print_at_level(FILE* file, int level, char* text);

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

void
ast_to_json(ast_node_t* root, FILE* file)
{
  _ast_to_json_aux(root, file, 0);
  fputc('\n', file);
}

#define _JSON_PRINT_FIELD(level, name, fmt, ...)                                                                       \
  _print_at_level(file, level, "\"" name "\": ");                                                                      \
  fprintf(file, fmt, __VA_ARGS__);

static void
_ast_to_json_aux(ast_node_t* root, FILE* file, int level)
{
  _print_at_level(file, level, "{\n");

  _JSON_PRINT_FIELD(level + 1, "type", "\"%s\",\n", mya_node_types[root->type]);

  if (root->token != NULL) {
    _JSON_PRINT_FIELD(level + 1, "token", "%s", "{\n");
    _JSON_PRINT_FIELD(level + 2, "lexeme", "\"%s\",\n", root->token->lexeme.data);
    _JSON_PRINT_FIELD(level + 2, "type", "\"%s\",\n", mya_token_types[root->token->type]);
    _JSON_PRINT_FIELD(level + 2, "line", "%d,\n", root->token->line);
    _JSON_PRINT_FIELD(level + 2, "column", "%d,\n", root->token->column);
    _JSON_PRINT_FIELD(level + 2, "value", "%lld\n", root->token->value);
    _print_at_level(file, level + 1, "},\n");
  }

  if (root->children_count == 0) {
    _JSON_PRINT_FIELD(level + 1, "children", "%s", "[]\n");
  } else {
    _JSON_PRINT_FIELD(level + 1, "children", "%s", "[\n");
    for (int i = 0; i < root->children_count; i++) {
      _ast_to_json_aux(&root->children[i], file, level + 2);

      fputs((i < root->children_count - 1 ? ",\n" : "\n"), file);
    }
    _print_at_level(file, level + 1, "]\n");
  }

  _print_at_level(file, level, "}");
}

static void
_print_at_level(FILE* file, int level, char* text)
{
  if (level <= 0) {
    fputs(text, file);
    return;
  }

  fprintf(file, "%*c%s", level * 2, ' ', text);
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
