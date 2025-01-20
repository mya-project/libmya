#include "ast.h"
#include "token.h"
#include "unity.h"

void
test_ast_node_init(void)
{
  ast_node_t node;
  token_t token;

  token_init(&token, "+", TK_OPERATOR, 1, 2);

  ast_node_init(&node, NULL, NT_EXPRESSION, &token);

  TEST_ASSERT_NULL(node.parent);
  TEST_ASSERT_EQUAL(NT_EXPRESSION, node.type);
  TEST_ASSERT_EQUAL(&token, node.token);
  TEST_ASSERT_EQUAL(0, node.children_count);
  TEST_ASSERT_EQUAL(AST_INITIAL_CHILDREN_LENGTH, node._children_length);

  ast_close(&node);
}

void
test_ast_add_children(void)
{
  ast_node_t root;
  token_t root_token;
  token_t child_token;

  token_init(&root_token, "inst", TK_KEYWORD, 1, 1);
  token_init(&child_token, "mov", TK_IDENTIFIER, 1, 5);

  ast_node_init(&root, NULL, NT_STATEMENT, &root_token);

  for (int i = 0; i < 300; i++) {
    ast_add_children(&root, NT_IDENTIFIER, &child_token);

    TEST_ASSERT_EQUAL(i + 1, root.children_count);
    TEST_ASSERT_GREATER_OR_EQUAL(root.children_count, root._children_length);

    TEST_ASSERT_EQUAL(&root, root.children[i].parent);
    TEST_ASSERT_EQUAL(NT_IDENTIFIER, root.children[i].type);
    TEST_ASSERT_EQUAL(&child_token, root.children[i].token);
  }

  ast_close(&root);
}

void
test_ast_insert_children(void)
{
  ast_node_t root;
  ast_node_t child;
  token_t root_token;
  token_t child_token;

  token_init(&root_token, "inst", TK_KEYWORD, 1, 1);
  token_init(&child_token, "mov", TK_IDENTIFIER, 1, 5);

  ast_node_init(&root, NULL, NT_STATEMENT, &root_token);

  for (int i = 0; i < 300; i++) {
    ast_node_init(&child, NULL, NT_IDENTIFIER, &child_token);
    ast_insert_children(&root, &child);

    TEST_ASSERT_EQUAL(i + 1, root.children_count);
    TEST_ASSERT_GREATER_OR_EQUAL(root.children_count, root._children_length);

    TEST_ASSERT_EQUAL(&root, root.children[i].parent);
    TEST_ASSERT_EQUAL(NT_IDENTIFIER, root.children[i].type);
    TEST_ASSERT_EQUAL(&child_token, root.children[i].token);
  }

  ast_close(&root);
}

void
test_ast_copy(void)
{
  ast_node_t parent;
  token_t token;

  ast_node_t source;
  ast_node_t destiny;

  ast_node_init(&source, &parent, NT_EXPRESSION, &token);

  ast_copy(&destiny, &source);

  TEST_ASSERT_EQUAL_MEMORY(&source, &destiny, sizeof(ast_node_t));
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_ast_node_init);
  RUN_TEST(test_ast_add_children);
  RUN_TEST(test_ast_insert_children);
  RUN_TEST(test_ast_copy);

  return UNITY_END();
}

void
setUp(void)
{
  //
}

void
tearDown(void)
{
  //
}
