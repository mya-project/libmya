#include <string.h>

#include "err.h"
#include "module.h"
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
}

void
test_module_init_with_filepath_bigger_than_maximum_expects_to_truncate(void)
{
  module_t module;

  error_code_t err = module_init(&module, FILE_BIG_PATH);
  TEST_ASSERT_EQUAL(ERR_OK, err);

  TEST_ASSERT_EQUAL(MODULE_MAX_FILEPATH_SIZE, strlen(module.filepath));
}
