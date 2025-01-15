#include "cqueue.c"
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
  RUN_TEST(test_module_add_token);
  RUN_TEST(test_module_getc);
  RUN_TEST(test_module_lookup);
  RUN_TEST(test_module_close);

  RUN_TEST(test_cqueue_init);
  RUN_TEST(test_cqueue_add);
  RUN_TEST(test_cqueue_get);
  RUN_TEST(test_cqueue_lookup);
  RUN_TEST(test_cqueue_isempty);
  RUN_TEST(test_cqueue_isfull);
  RUN_TEST(test_cqueue_circular_case);

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
