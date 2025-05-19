#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "evaluator.h"
#include "hashtable.h"
#include "module.h"
#include "mya.h"
#include "parser.h"
#include "unity.h"
#include "utils.h"

void
test_evaluator_with_simple_expression(void)
{
  module_t module;
  hashtable_t vars;

  hashtable_init(&vars, 10);

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_SIMPLE_EXPRESSION));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  parse_expression(&module, &module.ast, module.tokens);
  TEST_ASSERT_EQUAL(0, module.errors_count);

  int64_t result = eval_expression(&vars, &module, &module.ast.children[0]);
  TEST_ASSERT_EQUAL(11, result);

  module_close(&module);
  hashtable_close(&vars);
}

void
test_evaluator_with_expression(void)
{
  module_t module;
  hashtable_t vars;

  hashtable_init(&vars, 10);

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_EXPRESSION));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));

  parse_expression(&module, &module.ast, module.tokens);
  TEST_ASSERT_EQUAL(0, module.errors_count);

  int64_t result = eval_expression(&vars, &module, &module.ast.children[0]);
  TEST_ASSERT_EQUAL(83485, result);

  module_close(&module);
  hashtable_close(&vars);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_evaluator_with_simple_expression);
  RUN_TEST(test_evaluator_with_expression);

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
