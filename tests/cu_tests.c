#include "CUnit/Basic.h"

#include "../inc/utils.h"

void testArgumentParsing(void)
{
  char* argv[] = {"/usr/bin/test_runner", "-vid", "0x0483", "-pid", "0x5740"};
  int argc = 5;
  __uint16_t vid, pid;

  CU_ASSERT(parseArgs(argc, argv, &vid, &pid) == UTILS_OK);
  CU_ASSERT(vid == 0x0483);
  CU_ASSERT(pid == 0x5740);
}

int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("main suite", NULL, NULL);

   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if (NULL == CU_add_test(pSuite, "argument parsing test", testArgumentParsing)) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
