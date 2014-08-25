#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <math.h>
#include "emath.h"

void test_emath_mod(void)
{
  CU_ASSERT_EQUAL(FMOD( 1.0, 3.0), 1.0);
  CU_ASSERT_EQUAL(FMOD(-1.0, 3.0), 2.0);
}

void test_emath_pow(void)
{
  CU_ASSERT_EQUAL(pow(2.0, 2.0), ipow(2.0, 2));
  CU_ASSERT_EQUAL(pow(2.0, 3.0), ipow(2.0, 3));
  CU_ASSERT_EQUAL(pow(2.0, -2.0), ipow(2.0, -2));
  CU_ASSERT_EQUAL(pow(2.0, -3.0), ipow(2.0, -3));
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("emath", NULL, NULL);
  CU_add_test(s, "test_mod", test_emath_mod);
  CU_add_test(s, "test_pow", test_emath_pow);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

