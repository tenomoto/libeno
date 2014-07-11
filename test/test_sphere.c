#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "sphere.h"

void test_sphere_orthodrome(void)
{
  CU_ASSERT_EQUAL(eno_sphere_orthodrome(0.0, 0, 0.0, M_PI), M_PI);
}

void test_sphere_helix(void)
{
  const int n = 3;
  double lon[n];
  double colat[n];
  double k = sqrt(n*M_PI);

  eno_sphere_helix(n, lon, colat);
  CU_ASSERT_EQUAL(colat[0], acos(1.0-1.0/3.0));
  CU_ASSERT_EQUAL(colat[1], acos(0.0));
  CU_ASSERT_EQUAL(colat[2], acos(1.0-5.0/3.0));
  for (int i; i<n; i++) {
    CU_ASSERT_EQUAL(lon[i], fmod(k*colat[i], 2*M_PI));
  }
}

void test_sphere_generalized_spiral(void)
{
  const int n = 3;
  double lon[n];
  double colat[n];

  eno_sphere_generalized_spiral(n, lon, colat);
  CU_ASSERT_EQUAL(colat[0], M_PI);
  CU_ASSERT_EQUAL(colat[1], M_PI_2);
  CU_ASSERT_EQUAL(colat[2], 0.0);
  CU_ASSERT_EQUAL(lon[0], 0.0);
  CU_ASSERT_EQUAL(lon[2], 0.0);
}

void test_sphere_fibonacci(void)
{
  const int n = 3;
  double lon[n];
  double colat[n];

  const double phir = 2.0/(1.0 + sqrt(5.0));
  double m = n*M_PI*phir;

  eno_sphere_fibonacci(n, lon, colat);
  for (int i; i<n; i++) {
    double h = 1.0 - (2.0*i+1.0)/n;
    CU_ASSERT_EQUAL(colat[0], acos(h));
    CU_ASSERT_EQUAL(lon[0], eno_emath_mod(-m*h,2*M_PI));
  }
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("spherical_helix", NULL, NULL);
  CU_add_test(s, "sphere_orthodrome", test_sphere_orthodrome);
  CU_add_test(s, "sphere_helix", test_sphere_helix);
  CU_add_test(s, "sphere_generalized_spiral", test_sphere_generalized_spiral);
  CU_add_test(s, "sphere_generalized_spiral", test_sphere_fibonacci);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

