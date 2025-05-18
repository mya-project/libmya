#include "ast.h"
#include "tkstack.h"
#include "unity.h"

void
test_tkstack_init(void)
{
  tkstack_t stack;

  tkstack_init(&stack);

  TEST_ASSERT_EQUAL(0, stack.length);
  TEST_ASSERT_EQUAL(TKSTACK_INITIAL_LENGTH, stack._size);
  TEST_ASSERT_NOT_NULL(stack.values);

  tkstack_close(&stack);
}

void
test_tkstack_push_and_pop(void)
{
  tkstack_t stack;
  tkstack_init(&stack);

  token_t* token = NULL;

  tkstack_push(&stack, token + 0);
  tkstack_push(&stack, token + 1);
  tkstack_push(&stack, token + 2);

  TEST_ASSERT_EQUAL_PTR(token + 2, tkstack_pop(&stack));
  TEST_ASSERT_EQUAL_PTR(token + 1, tkstack_pop(&stack));
  TEST_ASSERT_EQUAL_PTR(token + 0, tkstack_pop(&stack));

  tkstack_close(&stack);
}

void
test_tkstack_isempty(void)
{
  tkstack_t stack;
  tkstack_init(&stack);

  TEST_ASSERT_TRUE(tkstack_isempty(&stack));

  tkstack_push(&stack, NULL);
  tkstack_push(&stack, NULL);

  TEST_ASSERT_FALSE(tkstack_isempty(&stack));

  tkstack_pop(&stack);
  TEST_ASSERT_FALSE(tkstack_isempty(&stack));

  tkstack_pop(&stack);
  TEST_ASSERT_TRUE(tkstack_isempty(&stack));

  tkstack_close(&stack);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_tkstack_init);
  RUN_TEST(test_tkstack_push_and_pop);
  RUN_TEST(test_tkstack_isempty);

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
