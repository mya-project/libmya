#include "mya.h"
#include "types/keywords.h"
#include "unity.h"
#include "utils.h"

#define _assert_token(_module, _type, _lexeme, _value, _line, _column)                                                 \
  TEST_ASSERT_MESSAGE(tkindex < _module.tokens_count, "Here is no more tokens on the module.");                        \
  TEST_ASSERT_EQUAL_MESSAGE(_type, _module.tokens[tkindex].type, "Unexpected token type.");                            \
  TEST_ASSERT_EQUAL_MESSAGE(_line, _module.tokens[tkindex].line, "Token line is wrong.");                              \
  TEST_ASSERT_EQUAL_MESSAGE(_column, _module.tokens[tkindex].column, "Token column is wrong.");                        \
  TEST_ASSERT_EQUAL_MESSAGE(_value, _module.tokens[tkindex].value, "Token value is wrong.");                           \
  TEST_ASSERT_EQUAL_STRING_MESSAGE(_lexeme, _module.tokens[tkindex].lexeme.data, "Token lexeme is wrong");             \
  tkindex++;

void
test_lexer_with_math_expression(void)
{
  module_t module;
  int tkindex = 0;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_EXPRESSION));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(17, module.tokens_count);

  _assert_token(module, TK_NUMBER, "1", 1, 1, 1);
  _assert_token(module, TK_OPERATOR, "+", 0, 1, 2);
  _assert_token(module, TK_NUMBER, "1", 1, 1, 3);
  _assert_token(module, TK_OPERATOR, "*", 0, 1, 5);
  _assert_token(module, TK_OPEN_PARENS, "(", 0, 1, 7);
  _assert_token(module, TK_NUMBER, "345", 345, 1, 8);
  _assert_token(module, TK_OPERATOR, "+", 0, 1, 12);
  _assert_token(module, TK_NUMBER, "0xa1b2", 41394, 1, 14);
  _assert_token(module, TK_CLOSE_PARENS, ")", 0, 1, 20);
  _assert_token(module, TK_OPERATOR, "-", 0, 1, 22);
  _assert_token(module, TK_NUMBER, "0b1010", 10, 1, 24);
  _assert_token(module, TK_OPERATOR, "+", 0, 1, 31);
  _assert_token(module, TK_NUMBER, "099", 99, 1, 33);
  _assert_token(module, TK_OPERATOR, "/", 0, 1, 37);
  _assert_token(module, TK_OPEN_PARENS, "(", 0, 1, 39);
  _assert_token(module, TK_NUMBER, "0o7", 7, 1, 42);
  _assert_token(module, TK_CLOSE_PARENS, ")", 0, 1, 47);
}

void
test_lexer_with_basic_module(void)
{
  module_t module;
  int tkindex = 0;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(45, module.tokens_count);

  _assert_token(module, TK_KEYWORD, "bitfield", KEY_BITFIELD, 1, 1);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 1, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 1, 13);
  _assert_token(module, TK_NUMBER, "4", 4, 1, 14);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 1, 15);

  _assert_token(module, TK_KEYWORD, "register", KEY_REGISTER, 4, 1);
  _assert_token(module, TK_IDENTIFIER, "r0", 0, 4, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 4, 12);
  _assert_token(module, TK_NUMBER, "32", 32, 4, 13);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 4, 15);
  _assert_token(module, TK_OPERATOR, "=", 0, 4, 17);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 4, 19);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 4, 22);
  _assert_token(module, TK_NUMBER, "0", 0, 4, 23);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 4, 24);

  _assert_token(module, TK_KEYWORD, "register", KEY_REGISTER, 5, 1);
  _assert_token(module, TK_IDENTIFIER, "r1", 0, 5, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 5, 12);
  _assert_token(module, TK_NUMBER, "32", 32, 5, 13);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 5, 15);
  _assert_token(module, TK_OPERATOR, "=", 0, 5, 17);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 5, 19);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 5, 22);
  _assert_token(module, TK_NUMBER, "0x1", 1, 5, 23);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 5, 26);

  _assert_token(module, TK_KEYWORD, "register", KEY_REGISTER, 6, 1);
  _assert_token(module, TK_IDENTIFIER, "r2", 0, 6, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 6, 12);
  _assert_token(module, TK_NUMBER, "32", 32, 6, 13);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 6, 15);
  _assert_token(module, TK_OPERATOR, "=", 0, 6, 17);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 6, 19);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 6, 22);
  _assert_token(module, TK_NUMBER, "0b10", 2, 6, 23);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 6, 27);

  _assert_token(module, TK_KEYWORD, "register", KEY_REGISTER, 7, 1);
  _assert_token(module, TK_IDENTIFIER, "r3", 0, 7, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 7, 12);
  _assert_token(module, TK_NUMBER, "32", 32, 7, 13);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 7, 15);
  _assert_token(module, TK_OPERATOR, "=", 0, 7, 17);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 7, 19);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 7, 23);
  _assert_token(module, TK_NUMBER, "0o3", 3, 7, 25);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 7, 29);
}

void
test_lexer_with_instructions_module(void)
{
  module_t module;
  int tkindex = 0;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_INSTRUCTIONS_MODULE));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(79, module.tokens_count);

  _assert_token(module, TK_KEYWORD, "include", KEY_INCLUDE, 1, 1);
  _assert_token(module, TK_STRING, "tests/utils/basic.mya", 0, 1, 9);

  _assert_token(module, TK_KEYWORD, "bitfield", KEY_BITFIELD, 3, 1);
  _assert_token(module, TK_IDENTIFIER, "Opcode", 0, 3, 10);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 3, 16);
  _assert_token(module, TK_NUMBER, "8", 8, 3, 17);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 3, 18);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 3, 20);

  _assert_token(module, TK_IDENTIFIER, "imm", 0, 4, 5);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 4, 8);
  _assert_token(module, TK_NUMBER, "1", 1, 4, 9);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 4, 10);

  _assert_token(module, TK_IDENTIFIER, "op", 0, 5, 5);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 5, 7);
  _assert_token(module, TK_NUMBER, "4", 4, 5, 8);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 5, 9);

  _assert_token(module, TK_IDENTIFIER, "reg", 0, 6, 5);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 6, 8);
  _assert_token(module, TK_NUMBER, "3", 3, 6, 9);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 6, 10);

  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 7, 1);

  _assert_token(module, TK_KEYWORD, "set", KEY_SET, 9, 1);
  _assert_token(module, TK_IDENTIFIER, "INSTRUCTION_MAX_SIZE", 0, 9, 5);
  _assert_token(module, TK_OPERATOR, "=", 0, 9, 26);
  _assert_token(module, TK_NUMBER, "16", 16, 9, 28);
  _assert_token(module, TK_SEMICOLON, ";", 0, 9, 30);

  _assert_token(module, TK_KEYWORD, "set", KEY_SET, 10, 1);
  _assert_token(module, TK_IDENTIFIER, "INSTRUCTION_MIN_SIZE", 0, 10, 5);
  _assert_token(module, TK_OPERATOR, "=", 0, 10, 26);
  _assert_token(module, TK_NUMBER, "16", 16, 10, 28);
  _assert_token(module, TK_SEMICOLON, ";", 0, 10, 30);

  _assert_token(module, TK_KEYWORD, "inst", KEY_INST, 12, 1);
  _assert_token(module, TK_IDENTIFIER, "mov", 0, 12, 6);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 12, 9);
  _assert_token(module, TK_NUMBER, "16", 16, 12, 10);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 12, 12);
  _assert_token(module, TK_OPEN_PARENS, "(", 0, 12, 13);
  _assert_token(module, TK_IDENTIFIER, "arg1", 0, 12, 14);
  _assert_token(module, TK_COLON, ":", 0, 12, 18);
  _assert_token(module, TK_KEYWORD, "register", KEY_REGISTER, 12, 20);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 12, 28);
  _assert_token(module, TK_NUMBER, "32", 32, 12, 29);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 12, 31);
  _assert_token(module, TK_COMMA, ",", 0, 12, 32);
  _assert_token(module, TK_IDENTIFIER, "arg2", 0, 12, 34);
  _assert_token(module, TK_COLON, ":", 0, 12, 38);
  _assert_token(module, TK_KEYWORD, "immediate", KEY_IMMEDIATE, 12, 40);
  _assert_token(module, TK_OPEN_BRACKET, "[", 0, 12, 49);
  _assert_token(module, TK_NUMBER, "8", 8, 12, 50);
  _assert_token(module, TK_CLOSE_BRACKET, "]", 0, 12, 51);
  _assert_token(module, TK_CLOSE_PARENS, ")", 0, 12, 52);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 12, 54);

  _assert_token(module, TK_IDENTIFIER, "opcode", 0, 13, 5);
  _assert_token(module, TK_OPERATOR, "=", 0, 13, 12);
  _assert_token(module, TK_IDENTIFIER, "Opcode", 0, 13, 14);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 13, 21);

  _assert_token(module, TK_IDENTIFIER, "imm", 0, 14, 9);
  _assert_token(module, TK_OPERATOR, "=", 0, 14, 13);
  _assert_token(module, TK_NUMBER, "0b1", 1, 14, 15);
  _assert_token(module, TK_COMMA, ",", 0, 14, 18);

  _assert_token(module, TK_IDENTIFIER, "op", 0, 15, 9);
  _assert_token(module, TK_OPERATOR, "=", 0, 15, 12);
  _assert_token(module, TK_NUMBER, "0x00", 0, 15, 14);
  _assert_token(module, TK_COMMA, ",", 0, 15, 18);

  _assert_token(module, TK_IDENTIFIER, "reg", 0, 16, 9);
  _assert_token(module, TK_OPERATOR, "=", 0, 16, 13);
  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 16, 15);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 16, 18);
  _assert_token(module, TK_IDENTIFIER, "arg1", 0, 16, 19);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 16, 23);
  _assert_token(module, TK_COMMA, ",", 0, 16, 24);

  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 17, 5);
  _assert_token(module, TK_COMMA, ",", 0, 17, 6);

  _assert_token(module, TK_IDENTIFIER, "Reg", 0, 18, 5);
  _assert_token(module, TK_OPEN_BRACES, "{", 0, 18, 8);
  _assert_token(module, TK_IDENTIFIER, "arg2", 0, 18, 9);
  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 18, 13);
  _assert_token(module, TK_COMMA, ",", 0, 18, 14);

  _assert_token(module, TK_CLOSE_BRACES, "}", 0, 19, 1);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_lexer_with_math_expression);
  RUN_TEST(test_lexer_with_basic_module);
  RUN_TEST(test_lexer_with_instructions_module);

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
