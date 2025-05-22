#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "evaluator.h"
#include "hashtable.h"
#include "mir.h"
#include "module.h"
#include "mya.h"
#include "parser.h"
#include "unity.h"
#include "utils.h"

#define _ASSERT_LITERAL_SPEC(_spec, _name, _value)                                                                     \
  TEST_ASSERT_EQUAL_STRING(_name, (_spec).name.data);                                                                  \
  TEST_ASSERT_EQUAL(FT_LITERAL, (_spec).type);                                                                         \
  TEST_ASSERT_EQUAL(_value, (_spec).value);                                                                            \
  TEST_ASSERT_EQUAL(0, (_spec).spec_length)

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

void
test_evaluator_with_basic_module(void)
{
  module_t module;
  mir_t mir;

  mir_init(&mir);

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));
  TEST_ASSERT_EQUAL(ERR_OK, mya_lexer(&module));
  TEST_ASSERT_EQUAL(ERR_OK, mya_parser(&module));
  TEST_ASSERT_EQUAL(ERR_OK, mya_evaluator(&mir, &module));
  TEST_ASSERT_EQUAL(0, module.errors_count);

  TEST_ASSERT_EQUAL(1, mir.bitfields_length);
  TEST_ASSERT_EQUAL(4, mir.registers_length);

  mir_bitfield_t* bfreg = mir_get_bitfield(&mir, "Reg");
  TEST_ASSERT_EQUAL_STRING("Reg", bfreg->name.data);
  TEST_ASSERT_EQUAL(4, bfreg->size);
  TEST_ASSERT_EQUAL(0, bfreg->fields_length);

  mir_register_t* r0 = mir_get_register(&mir, "r0");
  TEST_ASSERT_EQUAL_STRING("r0", r0->name.data);
  TEST_ASSERT_EQUAL(32, r0->size);
  _ASSERT_LITERAL_SPEC(r0->spec, "Reg", 0);

  mir_register_t* r1 = mir_get_register(&mir, "r1");
  TEST_ASSERT_EQUAL_STRING("r1", r1->name.data);
  TEST_ASSERT_EQUAL(32, r1->size);
  _ASSERT_LITERAL_SPEC(r1->spec, "Reg", 1);

  mir_register_t* r2 = mir_get_register(&mir, "r2");
  TEST_ASSERT_EQUAL_STRING("r2", r2->name.data);
  TEST_ASSERT_EQUAL(32, r2->size);
  _ASSERT_LITERAL_SPEC(r2->spec, "Reg", 2);

  mir_register_t* r3 = mir_get_register(&mir, "r3");
  TEST_ASSERT_EQUAL_STRING("r3", r3->name.data);
  TEST_ASSERT_EQUAL(32, r3->size);
  _ASSERT_LITERAL_SPEC(r3->spec, "Reg", 3);

  module_close(&module);
  mir_close(&mir);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_evaluator_with_simple_expression);
  RUN_TEST(test_evaluator_with_expression);
  RUN_TEST(test_evaluator_with_basic_module);

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
