#include <string.h>

#include "dstring.h"
#include "unity.h"

void
test_dstring_init(void)
{
  dstring_t string;

  dstring_init(&string, 21);

  TEST_ASSERT_EQUAL(0, string.length);
  TEST_ASSERT_EQUAL(21, string._buffer_size);
  TEST_ASSERT_NOT_NULL(string.data);

  dstring_close(&string);
}

void
test_dstring_close(void)
{
  dstring_t string;

  dstring_init(&string, 21);

  dstring_close(&string);

  TEST_ASSERT_NULL(string.data);
}

void
test_dstring_putchar(void)
{
  dstring_t string;

  dstring_init(&string, 25);

  for (int i = 0; i < 999; i++) {
    dstring_putchar(&string, 'x');
  }

  TEST_ASSERT_EACH_EQUAL_CHAR('x', string.data, 999);
  TEST_ASSERT_GREATER_THAN(999, string._buffer_size);

  dstring_close(&string);
}

void
test_dstring_concat(void)
{
  dstring_t string;

  dstring_init(&string, 25);

  dstring_concat(&string, "abc");
  dstring_concat(&string, "def");
  dstring_concat(&string, "ghij");

  TEST_ASSERT_EQUAL_STRING("abcdefghij", string.data);

  for (int i = 0; i < 300; i++) {
    dstring_concat(&string, "xxx");
  }

  TEST_ASSERT_EACH_EQUAL_CHAR('x', string.data + 10, 900);
  TEST_ASSERT_GREATER_THAN(910, string._buffer_size);

  dstring_close(&string);
}

void
test_dstring_copy(void)
{
  dstring_t string;

  dstring_init(&string, 5);

  char* expected = "Any string bigger than the allocated buffer of the string.";
  size_t expected_length = strlen(expected);

  dstring_copy(&string, expected);

  TEST_ASSERT_EQUAL_STRING(expected, string.data);
  TEST_ASSERT_EQUAL(expected_length, string.length);

  TEST_ASSERT_GREATER_THAN(expected_length, string._buffer_size);

  dstring_close(&string);
}

//////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_dstring_init);
  RUN_TEST(test_dstring_close);
  RUN_TEST(test_dstring_putchar);
  RUN_TEST(test_dstring_concat);
  RUN_TEST(test_dstring_copy);

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
