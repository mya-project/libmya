#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "types/err.h"
#include "unity.h"

void
test_cqueue_init(void)
{
  cqueue_t queue;

  cqueue_init(&queue, 500);

  TEST_ASSERT_EQUAL(0, queue.length);
  TEST_ASSERT_EQUAL(0, queue._current);
  TEST_ASSERT_EQUAL(-1, queue._last);
  TEST_ASSERT_EQUAL(500, queue._max_length);
  TEST_ASSERT_NOT_NULL(queue.data);

  memset(queue.data, 0, sizeof(int) * 500);

  free(queue.data);
}

void
test_cqueue_add(void)
{
  cqueue_t queue;

  cqueue_init(&queue, 5);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 3));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 4));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 5));

  TEST_ASSERT_EQUAL_INT_ARRAY(((int[]){ 1, 2, 3, 4, 5 }), queue.data, 5);
  TEST_ASSERT_EQUAL(5, queue.length);

  TEST_ASSERT_EQUAL(ERR_MAX_SIZE_EXCEEDED, cqueue_add(&queue, 6));

  free(queue.data);
}

void
test_cqueue_get(void)
{
  cqueue_t queue;
  int value;

  cqueue_init(&queue, 3);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 3));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(1, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(3, value);

  TEST_ASSERT_EQUAL(0, queue.length);

  TEST_ASSERT_EQUAL(ERR_EMPTY, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(3, value);  // Expects to not change the value.

  free(queue.data);
}

void
test_cqueue_lookup(void)
{
  cqueue_t queue;
  int value = -1;

  cqueue_init(&queue, 3);

  TEST_ASSERT_EQUAL(ERR_EMPTY, cqueue_lookup(&queue, &value, 0));
  TEST_ASSERT_EQUAL(-1, value);  // Expects to not change the value.

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 3));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 0));
  TEST_ASSERT_EQUAL(1, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 2));
  TEST_ASSERT_EQUAL(3, value);

  TEST_ASSERT_EQUAL(ERR_INVALID_INDEX, cqueue_lookup(&queue, &value, 3));
  TEST_ASSERT_EQUAL(3, value);  // Expects to not change the value.

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(1, value);

  free(queue.data);
}

void
test_cqueue_isempty(void)
{
  cqueue_t queue;
  int value;

  cqueue_init(&queue, 3);

  TEST_ASSERT_TRUE(cqueue_isempty(&queue));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_FALSE(cqueue_isempty(&queue));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_TRUE(cqueue_isempty(&queue));
}

void
test_cqueue_isfull(void)
{
  cqueue_t queue;
  int value;

  cqueue_init(&queue, 2);

  TEST_ASSERT_FALSE(cqueue_isfull(&queue));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_FALSE(cqueue_isfull(&queue));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_TRUE(cqueue_isfull(&queue));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_FALSE(cqueue_isfull(&queue));
}

void
test_cqueue_circular_case(void)
{
  cqueue_t queue;
  int value;

  cqueue_init(&queue, 3);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 3));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(1, value);
  TEST_ASSERT_EQUAL(1, queue._current);
  TEST_ASSERT_EQUAL(2, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(3, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(2, queue._current);
  TEST_ASSERT_EQUAL(2, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 4));
  TEST_ASSERT_EQUAL(2, queue._current);
  TEST_ASSERT_EQUAL(0, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 5));
  TEST_ASSERT_EQUAL(2, queue._current);
  TEST_ASSERT_EQUAL(1, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(4, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(3, value);
  TEST_ASSERT_EQUAL(0, queue._current);
  TEST_ASSERT_EQUAL(1, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(5, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(4, value);
  TEST_ASSERT_EQUAL(1, queue._current);
  TEST_ASSERT_EQUAL(1, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(5, value);
  TEST_ASSERT_EQUAL(2, queue._current);
  TEST_ASSERT_EQUAL(1, queue._last);

  TEST_ASSERT_TRUE(cqueue_isempty(&queue));

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 1));
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_add(&queue, 2));
  TEST_ASSERT_EQUAL(2, queue._current);
  TEST_ASSERT_EQUAL(0, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_lookup(&queue, &value, 1));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(1, value);
  TEST_ASSERT_EQUAL(0, queue._current);
  TEST_ASSERT_EQUAL(0, queue._last);

  TEST_ASSERT_EQUAL(ERR_OK, cqueue_get(&queue, &value));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(1, queue._current);
  TEST_ASSERT_EQUAL(0, queue._last);

  TEST_ASSERT_TRUE(cqueue_isempty(&queue));
}
