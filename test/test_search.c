#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "search.h"

void test_search(void)
{
  const int n = 5;
  double y1[n] = {1000.0, 850.0, 500.0, 300.0, 200.0};
  CU_ASSERT_EQUAL(eno_search_linear(y1, n, 1013.0, 0), -1);
  CU_ASSERT_EQUAL(eno_search_bisection(y1, n, 1013.0), -1);
  CU_ASSERT_EQUAL(eno_search_linear(y1, n,  925.0, 0),  0);
  CU_ASSERT_EQUAL(eno_search_bisection(y1, n,  925.0),  0);
  CU_ASSERT_EQUAL(eno_search_linear(y1, n,  250.0, 0),  3);
  CU_ASSERT_EQUAL(eno_search_bisection(y1, n,  250.0),  3);
  CU_ASSERT_EQUAL(eno_search_linear(y1, n,  150.0, 0),  4);
  CU_ASSERT_EQUAL(eno_search_bisection(y1, n,  150.0),  4);
  double y2[n] = {200.0, 300.0, 500.0, 850.0, 1000.0};
  CU_ASSERT_EQUAL(eno_search_linear(y2, n,  150.0, 0),  -1);
  CU_ASSERT_EQUAL(eno_search_bisection(y2, n,  150.0),  -1);
  CU_ASSERT_EQUAL(eno_search_linear(y2, n,  250.0, 0),   0);
  CU_ASSERT_EQUAL(eno_search_bisection(y2, n,  250.0),   0);
  CU_ASSERT_EQUAL(eno_search_linear(y2, n,  925.0, 0),   3);
  CU_ASSERT_EQUAL(eno_search_bisection(y2, n,  925.0),   3);
  CU_ASSERT_EQUAL(eno_search_linear(y2, n, 1013.0, 0),   4);
  CU_ASSERT_EQUAL(eno_search_bisection(y2, n, 1013.0),   4);
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("search", NULL, NULL);
  CU_add_test(s, "test_search", test_search);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

