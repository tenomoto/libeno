#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "extrapolate.h"

void test_extrapolate(void)
{
  const double gamma = 0.0065;
  const double Tl = 280.0;
  const double sigl = 0.98;
  double zs = 2000.0;
  CU_ASSERT(calc_y(gamma, sigl) < 0);
  double Ts = eno_extrapolate_Ts(Tl, sigl);
  CU_ASSERT(Ts > 0);
  double sig = 1.0;
  CU_ASSERT_EQUAL(calc_y(gamma, sig), 0.0);
  CU_ASSERT_EQUAL(eno_extrapolate_z(zs, Ts, sig),  zs);
  CU_ASSERT_EQUAL(eno_extrapolate_T(zs, Ts, sig),  Ts);
  sig = 1.2;
  CU_ASSERT(calc_y(gamma, sig) > 0);
  CU_ASSERT(eno_extrapolate_z(zs, Ts, sig) < zs);
  CU_ASSERT(eno_extrapolate_T(zs, Ts, sig) > Ts);
  double T1 = Ts + gamma * zs;
  double T2000 = eno_extrapolate_T(2000.0, Ts, sig);
  CU_ASSERT(T2000 < T1);
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("extrapolate", NULL, NULL);
  CU_add_test(s, "test_extrapolate", test_extrapolate);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

