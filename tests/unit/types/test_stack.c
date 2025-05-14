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

  stack_push(&stack, token + 0);
  stack_push(&stack, token + 1);
  stack_push(&stack, token + 2);

  TEST_ASSERT_EQUAL_PTR(token + 2, stack_pop(&stack));
  TEST_ASSERT_EQUAL_PTR(token + 1, stack_pop(&stack));
  TEST_ASSERT_EQUAL_PTR(token + 0, stack_pop(&stack));

  stack_close(&stack);
}

void
test_stack_isempty(void)
{
  stack_t stack;
  stack_init(&stack);

  TEST_ASSERT_TRUE(stack_isempty(&stack));

  stack_push(&stack, NULL);
  stack_push(&stack, NULL);

  TEST_ASSERT_FALSE(stack_isempty(&stack));

  stack_pop(&stack);
  TEST_ASSERT_FALSE(stack_isempty(&stack));

  stack_pop(&stack);
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
