#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "module.h"
#include "mya.h"
#include "parser.h"
#include "unity.h"
#include "utils.h"

void
_assert_files(char* file1, char* file2);

void
test_parser_with_expression(void)
{
  module_t module;
  char tmpname[] = "/tmp/XXXXXX";

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_EXPRESSION));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(0, module.errors_count);
  TEST_ASSERT_EQUAL(33, module.tokens_count);

  parse_expression(&module, &module.ast, module.tokens);

  TEST_ASSERT_EQUAL(0, module.errors_count);

  int fd = mkstemp(tmpname);
  FILE* tmp = fdopen(fd, "w");
  ast_to_json(&module.ast, tmp);

  fclose(tmp);

  _assert_files(tmpname, FILE_EXPRESSION ".json");

  unlink(tmpname);

  module_close(&module);
}

void
test_parser_with_basic_module(void)
{
  module_t module;
  char tmpname[] = "/tmp/XXXXXX";

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(0, module.errors_count);
  TEST_ASSERT_EQUAL(46, module.tokens_count);

  TEST_ASSERT_EQUAL(ERR_OK, mya_parser(&module));
  TEST_ASSERT_EQUAL(0, module.errors_count);

  int fd = mkstemp(tmpname);
  FILE* tmp = fdopen(fd, "w");
  ast_to_json(&module.ast, tmp);

  fclose(tmp);

  _assert_files(tmpname, FILE_BASIC_MODULE ".json");

  unlink(tmpname);

  module_close(&module);
}

void
test_parser_with_instructions_module(void)
{
  module_t module;
  char tmpname[] = "/tmp/XXXXXX";

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_INSTRUCTIONS_MODULE));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  TEST_ASSERT_EQUAL(0, module.errors_count);
  TEST_ASSERT_EQUAL(82, module.tokens_count);

  TEST_ASSERT_EQUAL(ERR_OK, mya_parser(&module));
  TEST_ASSERT_EQUAL(0, module.errors_count);


  int fd = mkstemp(tmpname);
  FILE* tmp = fdopen(fd, "w");
  ast_to_json(&module.ast, tmp);

  fclose(tmp);

  _assert_files(tmpname, FILE_INSTRUCTIONS_MODULE ".json");

  unlink(tmpname);

  module_close(&module);
}

/////

void
_assert_files(char* file1, char* file2)
{
  char cmd[128];

  snprintf(cmd, 127, "diff -u %s %s", file1, file2);

  TEST_ASSERT_EQUAL(0, system(cmd));
}

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_parser_with_expression);
  RUN_TEST(test_parser_with_basic_module);
  RUN_TEST(test_parser_with_instructions_module);

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
