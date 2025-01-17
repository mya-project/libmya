#include "mya.h"
#include "unity.h"
#include "utils.h"

void
_assert_token(
  module_t* module,
  token_type_t type,
  const char* lexeme,
  long long int value,
  unsigned int line,
  unsigned int column
);

void
test_lexer_with_math_expression(void)
{
  module_t module;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_EXPRESSION));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(17, module.tokens_count);

  _assert_token(&module, TK_NUMBER, "1", 1, 1, 1);
  _assert_token(&module, TK_OPERATOR, "+", 0, 1, 2);
  _assert_token(&module, TK_NUMBER, "1", 1, 1, 3);
  _assert_token(&module, TK_OPERATOR, "*", 0, 1, 5);
  _assert_token(&module, TK_OPEN_PARENS, "(", 0, 1, 7);
  _assert_token(&module, TK_NUMBER, "345", 345, 1, 8);
  _assert_token(&module, TK_OPERATOR, "+", 0, 1, 12);
  _assert_token(&module, TK_NUMBER, "0xa1b2", 41394, 1, 14);
  _assert_token(&module, TK_CLOSE_PARENS, ")", 0, 1, 20);
  _assert_token(&module, TK_OPERATOR, "-", 0, 1, 22);
  _assert_token(&module, TK_NUMBER, "0b1010", 10, 1, 24);
  _assert_token(&module, TK_OPERATOR, "+", 0, 1, 31);
  _assert_token(&module, TK_NUMBER, "099", 99, 1, 33);
  _assert_token(&module, TK_OPERATOR, "/", 0, 1, 37);
  _assert_token(&module, TK_OPEN_PARENS, "(", 0, 1, 39);
  _assert_token(&module, TK_NUMBER, "0o7", 7, 1, 42);
  _assert_token(&module, TK_CLOSE_PARENS, ")", 0, 1, 47);
}

/////

void
_assert_token(
  module_t* module,
  token_type_t type,
  const char* lexeme,
  long long int value,
  unsigned int line,
  unsigned int column
)
{
  static unsigned int tkindex = 0;

  TEST_ASSERT_MESSAGE(tkindex < module->tokens_count, "Here is no more tokens on the module.");


  TEST_ASSERT_EQUAL_MESSAGE(type, module->tokens[tkindex].type, "Unexpected token type.");
  TEST_ASSERT_EQUAL_MESSAGE(line, module->tokens[tkindex].line, "Token line is wrong.");
  TEST_ASSERT_EQUAL_MESSAGE(column, module->tokens[tkindex].column, "Token column is wrong.");
  TEST_ASSERT_EQUAL_MESSAGE(value, module->tokens[tkindex].value, "Token value is wrong.");
  TEST_ASSERT_EQUAL_STRING_MESSAGE(lexeme, module->tokens[tkindex].lexeme.data, "Token lexeme is wrong");

  tkindex++;
}

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_lexer_with_math_expression);

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
