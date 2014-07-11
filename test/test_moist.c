#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "air.h"
#include "moist.h"

void test_moist(void)
{
  const double T = 300.0;
  const double q =  10.0e-3;
  const double eps = eno_air_eps;
  double Tv = eno_moist_calc_Tv(T, q);
  CU_ASSERT_EQUAL(Tv, T*(1.0+(1.0-eps)/eps*q));
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("moist", NULL, NULL);
  CU_add_test(s, "test_moist", test_moist);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

