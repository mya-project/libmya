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
  TEST_ASSERT_EQUAL_STRING("any_token", token.lexeme);
}

void
test_token_init_with_lexeme_bigger_than_maximum_expects_to_truncate(void)
{
  token_t token;
  static char big[LEXEME_MAX_SIZE + 2];
  memset(big, 'x', LEXEME_MAX_SIZE + 1);

  token_init(&token, big, TK_KEYWORD, 2, 3);

  TEST_ASSERT_EQUAL_INT(LEXEME_MAX_SIZE, strlen(token.lexeme));
}
