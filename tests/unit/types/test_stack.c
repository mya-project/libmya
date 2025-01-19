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
}

void
test_stack_push_and_pop(void)
{
  stack_t stack;
  stack_init(&stack);

  stack_t* push_value = &stack;
  void* pop_value = NULL;

  for (int i = 0; i < 300; i++) {
    TEST_ASSERT_EQUAL(i, stack_push(&stack, push_value + i));

    TEST_ASSERT_EQUAL(i + 1, stack.length);
    TEST_ASSERT_GREATER_OR_EQUAL(stack.length, stack._size);
  }

  for (int i = 300; i > 0; i--) {
    TEST_ASSERT_EQUAL(ERR_OK, stack_pop(&stack, &pop_value));

    TEST_ASSERT_EQUAL(i - 1, stack.length);
    TEST_ASSERT_EQUAL(push_value + i - 1, pop_value);
  }

  TEST_ASSERT_EQUAL(0, stack.length);

  pop_value = NULL;
  TEST_ASSERT_EQUAL(ERR_EMPTY, stack_pop(&stack, &pop_value));
  TEST_ASSERT_NULL(pop_value);
}

void
test_stack_isempty(void)
{
  stack_t stack;
  stack_init(&stack);

  stack_t* push_value = &stack;
  void* pop_value = NULL;

  TEST_ASSERT_TRUE(stack_isempty(&stack));
  stack_push(&stack, push_value);
  stack_push(&stack, push_value + 1);
  TEST_ASSERT_FALSE(stack_isempty(&stack));
  stack_pop(&stack, &pop_value);
  TEST_ASSERT_FALSE(stack_isempty(&stack));
  stack_pop(&stack, &pop_value);
  TEST_ASSERT_TRUE(stack_isempty(&stack));
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
