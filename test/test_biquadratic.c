#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
//#include <CUnit/Console.h>
#include "biquadratic.h"

void test_biquadratic(double f[9], double d[9], double gx[9], double gy[9], double gxy[9])
{
  double c[9];

  double t[9] = {0.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.5};
  double u[9] = {0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5};
  double p, px, py, pxy;

#ifdef VERBOSE
  printf("\n");
  printf("coefficients\n");
#endif
  eno_biquadratic_coeff(f, c);
  for (int i=0; i<9; i++) {
    CU_ASSERT_EQUAL(c[i],d[i]);
#ifdef VERBOSE
    printf("c=%f, d=%f, c-d=%f\n", c[i], d[i], c[i]-d[i]);
#endif
  }

#ifdef VERBOSE
  printf("interpolate\n");
#endif
  for (int i=0; i<9; i++) {
    p   = eno_biquadratic_interpolate(c, t[i], u[i]);
    px  = eno_biquadratic_interpolate_x(c, t[i], u[i]);
    py  = eno_biquadratic_interpolate_y(c, t[i], u[i]);
    pxy = eno_biquadratic_interpolate_xy(c, t[i], u[i]);
    CU_ASSERT_EQUAL(p,   f[i]);
    CU_ASSERT_EQUAL(px,  gx[i]);
    CU_ASSERT_EQUAL(py,  gy[i]);
    CU_ASSERT_EQUAL(pxy, gxy[i]);
#ifdef VERBOSE
    printf("t=%f, u=%f, p=%f, f=%f, px=%f, gx=%f, py=%f, gy=%f, pxy=%f, gxy=%f\n", t[i], u[i], p, f[i], px, gx[i], py, gy[i], pxy, gxy[i]);
#endif
  }
}

void test_biquadratic_constant(void)
{
  double f[9]  = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double d[9]  = {1, 0, 0, 0, 0, 0, 0, 0, 0};
  double gx[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double gy[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double gxy[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  test_biquadratic(f, d, gx, gy, gxy);
}

void test_biquadratic_linear_x(void)
{
  double f[9]  = {0.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.5};
  double d[9]  = {0, 0, 0, 1, 0, 0, 0, 0, 0};
  double gx[9]  = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double gy[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double gxy[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  test_biquadratic(f, d, gx, gy, gxy);
}

void test_biquadratic_linear_y(void)
{
  double f[9]  = {0.0, 0.0, 0.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5};
  double d[9]  = {0, 1, 0, 0, 0, 0, 0, 0, 0};
  double gx[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  double gy[9]  = {1, 1, 1, 1, 1, 1, 1, 1, 1};
  double gxy[9]  = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  test_biquadratic(f, d, gx, gy, gxy);
}

/**
 * \f[ f = \sin(\pi x)\cos(\pi y) \f]
 * \f[ f_i = 4x-8xy-4x^2+8x^2y \f]
 */
void test_biquadratic_sincos(void)
{
  double f[9]   = { 0,  1,  0,  0,  0, -1,  0,  0,  0};
  double d[9]   = { 0,  0,  0,  4, -8,  0, -4,  8,  0};
  double gx[9]  = { 4,  0, -4,  0,  4,  0, -4,  0,  0};
  double gy[9]  = { 0, -2,  0,  0,  0, -2,  0,  0, -2};
  double gxy[9] = {-8,  0,  8,  8,  8,  0, -8, -8,  0};

  test_biquadratic(f, d, gx, gy, gxy);
}

/**
 * \f[ f = \cos(\pi x)\sin(\pi y) \f]
 * \f[ f_i = 4y-4y^2-8xy+8xy^2 \f]
 */
void test_biquadratic_cossin(void)
{
  double f[9]   = { 0,  0,  0, -1,  0,  0,  0,  1,  0};
  double d[9]   = { 0,  4, -4,  0, -8,  8,  0,  0,  0};
  double gx[9]  = { 0,  0,  0, -2,  0,  0,  0, -2, -2};
  double gy[9]  = { 4,  0, -4,  0,  4,  0, -4,  0,  0};
  double gxy[9] = {-8, -8, -8,  0,  8,  8,  8,  0,  0};

  test_biquadratic(f, d, gx, gy, gxy);
}

int main(void)
{
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("biquadratic", NULL, NULL);
  CU_add_test(s, "constant", test_biquadratic_constant);
  CU_add_test(s, "linear_x", test_biquadratic_linear_x);
  CU_add_test(s, "linear_y", test_biquadratic_linear_y);
  CU_add_test(s, "sincos",   test_biquadratic_sincos);
  CU_add_test(s, "cossin",   test_biquadratic_cossin);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
//  CU_console_run_tests();
  CU_cleanup_registry();

  return 0;
}
