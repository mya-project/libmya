#include <string.h>

#include "module.h"
#include "token.h"
#include "types/err.h"
#include "unity.h"
#include "utils.h"

void
test_module_init(void)
{
  module_t module;

  error_code_t err = module_init(&module, FILE_BASIC_MODULE);
  TEST_ASSERT_EQUAL(ERR_OK, err);

  TEST_ASSERT_NOT_NULL(module.file);
  TEST_ASSERT_EQUAL_STRING(FILE_BASIC_MODULE, module.filepath);
  TEST_ASSERT_NOT_NULL(module.tokens);
  TEST_ASSERT_EQUAL(0, module.tokens_count);
  TEST_ASSERT_EQUAL(MODULE_INITIAL_TOKENS_LENGTH, module._tokens_length);

  module_close(&module);
}

void
test_module_close(void)
{
  module_t module;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));
  module_close(&module);

  TEST_ASSERT_NULL(module.file);
  TEST_ASSERT_NULL(module._queue.data);
}

void
test_module_init_with_filepath_bigger_than_maximum_expects_to_truncate(void)
{
  module_t module;

  error_code_t err = module_init(&module, FILE_BIG_PATH);
  TEST_ASSERT_EQUAL(ERR_OK, err);

  TEST_ASSERT_EQUAL(MODULE_MAX_FILEPATH_SIZE, strlen(module.filepath));

  module_close(&module);
}

void
test_module_add_token(void)
{
  module_t module;
  error_code_t err = module_init(&module, FILE_BASIC_MODULE);
  TEST_ASSERT_EQUAL(ERR_OK, err);

  for (int i = 0; i < MODULE_INITIAL_TOKENS_LENGTH * 50; i++) {
    token_t* token = module_add_token(&module);

    TEST_ASSERT_NOT_NULL(token);

    token_init(token, "keyword", TK_KEYWORD, 1, 2);
  }

  module_close(&module);
}

void
test_module_getc(void)
{
  module_t module;
  int ch;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));

  TEST_ASSERT_EQUAL(ERR_OK, module_getc(&module, &ch));
  TEST_ASSERT_EQUAL('b', ch);
  TEST_ASSERT_EQUAL(ERR_OK, module_getc(&module, &ch));
  TEST_ASSERT_EQUAL('i', ch);
  TEST_ASSERT_EQUAL(ERR_OK, module_getc(&module, &ch));
  TEST_ASSERT_EQUAL('t', ch);

  module_close(&module);
}

void
test_module_lookup(void)
{
  module_t module;
  int ch;

  TEST_ASSERT_EQUAL(ERR_OK, module_init(&module, FILE_BASIC_MODULE));

  TEST_ASSERT_EQUAL(ERR_OK, module_lookup(&module, &ch, 0));
  TEST_ASSERT_EQUAL('b', ch);
  TEST_ASSERT_EQUAL(ERR_OK, module_lookup(&module, &ch, 1));
  TEST_ASSERT_EQUAL('i', ch);
  TEST_ASSERT_EQUAL(ERR_OK, module_lookup(&module, &ch, 2));
  TEST_ASSERT_EQUAL('t', ch);

  TEST_ASSERT_EQUAL(ERR_OK, module_getc(&module, &ch));
  TEST_ASSERT_EQUAL('b', ch);

  module_close(&module);
}

/////

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_module_init);
  RUN_TEST(test_module_close);
  RUN_TEST(test_module_init_with_filepath_bigger_than_maximum_expects_to_truncate);
  RUN_TEST(test_module_add_token);
  RUN_TEST(test_module_getc);
  RUN_TEST(test_module_lookup);

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
