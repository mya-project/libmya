#include "ast.h"
#include "stack.h"
#include "unity.h"

void
test_stack_init(void)
{
  stack_t stack;

  stack_init(&stack);

  TEST_ASSERT_EQUAL(0, stack.length);
  TEST_ASSERT_EQUAL(STACK_INITIAL_LENGTH, stack._size);
  TEST_ASSERT_NOT_NULL(stack.values);

  stack_close(&stack);
}

void
test_stack_push_and_pop(void)
{
  stack_t stack;
  stack_init(&stack);

  token_t* token = NULL;
  ast_node_t pop_node;

  for (int i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL(&stack.values[i], stack_push(&stack, NT_EXPRESSION, token + i));

    TEST_ASSERT_EQUAL(i + 1, stack.length);
    TEST_ASSERT_GREATER_OR_EQUAL(stack.length, stack._size);
  }

  for (int i = 300; i > 0; i--) {
    TEST_ASSERT_EQUAL(ERR_OK, stack_pop(&stack, &pop_node));

    TEST_ASSERT_EQUAL(i - 1, stack.length);
    TEST_ASSERT_EQUAL(NT_EXPRESSION, pop_node.type);
    TEST_ASSERT_EQUAL(token + i - 1, pop_node.token);
  }

  TEST_ASSERT_EQUAL(0, stack.length);

  TEST_ASSERT_EQUAL(ERR_EMPTY, stack_pop(&stack, &pop_node));

  stack_close(&stack);
}

void
test_stack_insert(void)
{
  stack_t stack;
  stack_init(&stack);

  token_t* token = NULL;
  ast_node_t insert_node;
  ast_node_t pop_node;

  ast_node_init(&insert_node, NULL, NT_EXPRESSION, NULL);

  for (int i = 0; i < 300; i++) {
    insert_node.token = token + i;
    TEST_ASSERT_EQUAL(&stack.values[i], stack_insert(&stack, &insert_node));

    TEST_ASSERT_EQUAL(i + 1, stack.length);
    TEST_ASSERT_GREATER_OR_EQUAL(stack.length, stack._size);
  }

  for (int i = 300; i > 0; i--) {
    TEST_ASSERT_EQUAL(ERR_OK, stack_pop(&stack, &pop_node));

    TEST_ASSERT_EQUAL(i - 1, stack.length);
    TEST_ASSERT_EQUAL(NT_EXPRESSION, pop_node.type);
    TEST_ASSERT_EQUAL(token + i - 1, pop_node.token);
  }

  TEST_ASSERT_EQUAL(0, stack.length);

  TEST_ASSERT_EQUAL(ERR_EMPTY, stack_pop(&stack, &pop_node));

  stack_close(&stack);
}

void
test_stack_isempty(void)
{
  stack_t stack;
  stack_init(&stack);

  ast_node_t pop_node;

  TEST_ASSERT_TRUE(stack_isempty(&stack));
  stack_push(&stack, NT_EXPRESSION, NULL);
  stack_push(&stack, NT_EXPRESSION, NULL);
  TEST_ASSERT_FALSE(stack_isempty(&stack));
  stack_pop(&stack, &pop_node);
  TEST_ASSERT_FALSE(stack_isempty(&stack));
  stack_pop(&stack, &pop_node);
  TEST_ASSERT_TRUE(stack_isempty(&stack));

  stack_close(&stack);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_stack_init);
  RUN_TEST(test_stack_push_and_pop);
  RUN_TEST(test_stack_insert);
  RUN_TEST(test_stack_isempty);

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
