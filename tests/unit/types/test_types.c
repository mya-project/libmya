#include "module.c"
#include "token.c"
#include "unity.h"

int
main(void)
{
  UNITY_BEGIN();

  RUN_TEST(test_token_init);
  RUN_TEST(test_token_init_with_lexeme_bigger_than_maximum_expects_to_truncate);

  RUN_TEST(test_module_init);
  RUN_TEST(test_module_init_with_filepath_bigger_than_maximum_expects_to_truncate);

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
