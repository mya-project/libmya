#include <string.h>

#include "tkqueue.h"
#include "unity.h"

void
test_tkqueue_init(void)
{
  tkqueue_t queue;

  tkqueue_init(&queue, 25);

  TEST_ASSERT_EQUAL(0, queue.length);
  TEST_ASSERT_EQUAL(0, queue._current);
  TEST_ASSERT_EQUAL(25, queue._size);
  TEST_ASSERT_NOT_NULL(queue.data);

  tkqueue_close(&queue);
}

void
test_tkqueue_add(void)
{
  tkqueue_t queue;
  token_t tk_a;
  token_t tk_b;
  token_t tk_c;
  token_t tk_d;

  tkqueue_init(&queue, 25);

  TEST_ASSERT_NULL(tkqueue_get(&queue));

  tkqueue_add(&queue, &tk_a);
  tkqueue_add(&queue, &tk_b);
  tkqueue_add(&queue, &tk_c);

  TEST_ASSERT_EQUAL_PTR(&tk_a, tkqueue_get(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_b, tkqueue_get(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_c, tkqueue_get(&queue));
  TEST_ASSERT_NULL(tkqueue_get(&queue));

  tkqueue_add(&queue, &tk_d);
  TEST_ASSERT_EQUAL_PTR(&tk_d, tkqueue_get(&queue));
  TEST_ASSERT_NULL(tkqueue_get(&queue));

  tkqueue_close(&queue);
}

void
test_tkqueue_lookup(void)
{
  tkqueue_t queue;
  token_t tk_a;
  token_t tk_b;

  tkqueue_init(&queue, 25);

  TEST_ASSERT_NULL(tkqueue_lookup(&queue));

  tkqueue_add(&queue, &tk_a);
  tkqueue_add(&queue, &tk_b);

  TEST_ASSERT_EQUAL_PTR(&tk_a, tkqueue_lookup(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_a, tkqueue_lookup(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_a, tkqueue_get(&queue));

  TEST_ASSERT_EQUAL_PTR(&tk_b, tkqueue_lookup(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_b, tkqueue_lookup(&queue));
  TEST_ASSERT_EQUAL_PTR(&tk_b, tkqueue_get(&queue));

  TEST_ASSERT_NULL(tkqueue_lookup(&queue));

  tkqueue_close(&queue);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_tkqueue_init);
  RUN_TEST(test_tkqueue_add);
  RUN_TEST(test_tkqueue_lookup);

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
