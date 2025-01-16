#include <string.h>

#include "token.h"
#include "unity.h"

void
test_token_init(void)
{
  token_t token;
  token_init(&token, "any_token", TK_KEYWORD, 2, 3);

  TEST_ASSERT_EQUAL(TK_KEYWORD, token.type);
  TEST_ASSERT_EQUAL(2, token.line);
  TEST_ASSERT_EQUAL(3, token.column);
  TEST_ASSERT_EQUAL_STRING("any_token", token.lexeme.data);
}

void
test_token_init_with_a_very_big_lexeme(void)
{
  token_t token;
  static char big[1001];

  memset(big, 'x', 1000);
  big[1000] = '\0';

  token_init(&token, big, TK_STRING, 2, 3);

  TEST_ASSERT_EQUAL_INT(1000, token.lexeme.length);
  TEST_ASSERT_EQUAL_STRING(big, token.lexeme.data);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_token_init);
  RUN_TEST(test_token_init_with_a_very_big_lexeme);

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
