#include <string.h>

#include "hashtable.h"
#include "unity.h"

void
test_hashtable_init(void)
{
  hashtable_t hashtable;

  hashtable_init(&hashtable, 100);

  TEST_ASSERT_EQUAL(hashtable._size, 100);
  TEST_ASSERT_NOT_NULL(hashtable.items);

  for (int i = 0; i < 100; i++) {
    hashtable.items[i].is_set = true;
    hashtable.items[i].value = 111;
  }

  hashtable_close(&hashtable);
}

void
test_hashtable_set_and_get(void)
{
  hashtable_t hashtable;
  int64_t value;

  hashtable_init(&hashtable, 1000);

  hashtable_set(&hashtable, "one", 1);
  hashtable_set(&hashtable, "two", 2);
  hashtable_set(&hashtable, "three", 3);

  TEST_ASSERT_EQUAL(ERR_OK, hashtable_get(&hashtable, "one", &value));
  TEST_ASSERT_EQUAL(1, value);
  TEST_ASSERT_EQUAL(ERR_OK, hashtable_get(&hashtable, "two", &value));
  TEST_ASSERT_EQUAL(2, value);
  TEST_ASSERT_EQUAL(ERR_OK, hashtable_get(&hashtable, "three", &value));
  TEST_ASSERT_EQUAL(3, value);

  hashtable_set(&hashtable, "one", 1111);
  TEST_ASSERT_EQUAL(ERR_OK, hashtable_get(&hashtable, "one", &value));
  TEST_ASSERT_EQUAL(1111, value);

  TEST_ASSERT_EQUAL(ERR_INVALID_INDEX, hashtable_get(&hashtable, "invalid", &value));

  hashtable_close(&hashtable);
}

void
test_hashtable_with_collisions(void)
{
  char key[10];
  hashtable_t hashtable;
  int64_t value;

  hashtable_init(&hashtable, 3);

  for (int i = 0; i < 100; i++) {
    sprintf(key, "key%d", i);
    hashtable_set(&hashtable, key, i);
  }

  for (int i = 0; i < 100; i++) {
    sprintf(key, "key%d", i);

    TEST_ASSERT_EQUAL(ERR_OK, hashtable_get(&hashtable, key, &value));
    TEST_ASSERT_EQUAL(i, value);
  }

  hashtable_close(&hashtable);
}

//////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_hashtable_init);
  RUN_TEST(test_hashtable_set_and_get);
  RUN_TEST(test_hashtable_with_collisions);

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
