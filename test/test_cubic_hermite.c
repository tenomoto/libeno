#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
//#include <CUnit/Console.h>
#include "cubic_hermite.h"

void test_cubic_hermite(double f[4], double d[4], double g[3], double gx[3])
{
  double c[4];

  double t[3] = {0.0, 0.5, 1.0};
  double p, px;

#ifdef VERBOSE
  printf("\n");
  printf("coefficients\n");
#endif
  eno_cubic_hermite_coeff(f, c);
  for (int i=0; i<4; i++) {
    CU_ASSERT_EQUAL(c[i],d[i]);
#ifdef VERBOSE
    printf("c=%f, d=%f\n", c[i], d[i]);
#endif
  }

#ifdef VERBOSE
  printf("interpolate\n");
#endif
  for (int i=0; i<3; i++) {
    p   = eno_cubic_hermite_interpolate(c, t[i]);
    px  = eno_cubic_hermite_interpolate_x(c, t[i]);
    CU_ASSERT_EQUAL(p,   g[i]);
    CU_ASSERT_EQUAL(px,  gx[i]);
#ifdef VERBOSE
    printf("t=%f, p=%f, g=%f, px=%f, gx=%f\n", t[i], p, g[i], px, gx[i]);
#endif
  }
}

void test_cubic_hermite_constant(void)
{
  double f[4]  = {1, 1, 0, 0};
  double d[4]  = {1, 0, 0, 0};
  double g[3]  = {1, 1, 1};
  double gx[5] = {0, 0, 0};

  test_cubic_hermite(f, d, g, gx);
}

void test_cubic_hermite_linear(void)
{
  double f[4]  = {0,   1,   1,  1};
  double d[4]  = {0,   1,   0,  0};
  double g[3]  = {0.0, 0.5, 1.0};
  double gx[5] = {1,   1,   1};

  test_cubic_hermite(f, d, g, gx);
}

/**
 * \f[ f = \cos(\pi x) \f]
 * \f[ f_i = x-x^2 \f]
 */
void test_cubic_hermite_cos(void)
{
  double f[4]  = {1, -1,  0, 0};
  double d[4]  = {1,  0, -6, 4};
  double g[3]  = {1,  0, -1};
  double gx[5] = {0, -3,  0}; /// analytic derivative at t=0.5 is \f$-\pi\f

  test_cubic_hermite(f, d, g, gx);
}

int main(void)
{
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("bicubic", NULL, NULL);
  CU_add_test(s, "constant", test_cubic_hermite_constant);
  CU_add_test(s, "linear", test_cubic_hermite_linear);
  CU_add_test(s, "cos",   test_cubic_hermite_cos);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
//  CU_console_run_tests();
  CU_cleanup_registry();

  return 0;
}
