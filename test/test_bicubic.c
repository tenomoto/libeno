#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
//#include <CUnit/Console.h>
#include "bicubic.h"

void test_bicubic(double f[16], double d[16], double g[5], double gx[5], double gy[5], double gxy[5])
{
  double c[16];

  double t[5] = {0.0, 1.0, 1.0, 0.0, 0.5};
  double u[5] = {0.0, 0.0, 1.0, 1.0, 0.5};
  double p, px, py, pxy;

  eno_bicubic_coeff(f, c);
  for (int i=0; i<16; i++) {
    CU_ASSERT_EQUAL(c[i],d[i]);
  }

  printf("\n");
  printf("coefficients\n");
  printf("interpolate\n");
  for (int i=0; i<5; i++) {
    p   = eno_bicubic_interpolate(c, t[i], u[i]);
    px  = eno_bicubic_interpolate_x(c, t[i], u[i]);
    py  = eno_bicubic_interpolate_y(c, t[i], u[i]);
    pxy = eno_bicubic_interpolate_xy(c, t[i], u[i]);
    CU_ASSERT_EQUAL(p,   g[i]);
    CU_ASSERT_EQUAL(px,  gx[i]);
    CU_ASSERT_EQUAL(py,  gy[i]);
    CU_ASSERT_EQUAL(pxy, gxy[i]);
    printf("t=%f, u=%f, p=%f, px=%f, py=%f, pxy=%f\n", t[i], u[i], p, px, py, pxy);
  }
}

void test_bicubic_constant(void)
{
  double f[16]  = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double d[16]  = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double g[5]   = {1, 1, 1, 1, 1};
  double gx[5]  = {0, 0, 0, 0, 0};
  double gy[5]  = {0, 0, 0, 0, 0};
  double gxy[5] = {0, 0, 0, 0, 0};

  test_bicubic(f, d, g, gx, gy, gxy);
}

void test_bicubic_linear_x(void)
{
  double f[16]  = {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
  double d[16]  = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double g[5]   = {0.0, 1.0, 1.0, 0.0, 0.5};
  double gx[5]  = {1.0, 1.0, 1.0, 1.0, 1.0};
  double gy[5]  = {0, 0, 0, 0, 0};
  double gxy[5] = {0, 0, 0, 0, 0};

  test_bicubic(f, d, g, gx, gy, gxy);
}

void test_bicubic_linear_y(void)
{
  double f[16]  = {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
  double d[16]  = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double g[5]   = {0.0, 0.0, 1.0, 1.0, 0.5};
  double gx[5]  = {0, 0, 0, 0, 0};
  double gy[5]  = {1.0, 1.0, 1.0, 1.0, 1.0};
  double gxy[5] = {0, 0, 0, 0, 0};

  test_bicubic(f, d, g, gx, gy, gxy);
}

/**
 * \f[ f = \sin(\pi x)\cos(\pi y)/\pi \f]
 * \f[ f_i = x-6xy^2+4xy^3-x^2+6x^2y^2-4x^2y^3 \f]
 */
void test_bicubic_sincos(void)
{
  double f[16]  = {0, 0, 0, 0, 1,-1, 1,-1, 0, 0, 0, 0, 0, 0, 0, 0};
  double d[16]  = {0, 0, 0, 0, 1, 0,-6, 4,-1, 0, 6,-4, 0, 0, 0, 0};
  double g[5]   = {0, 0, 0, 0, 0};
  double gx[5]  = {1,-1, 1,-1, 0};
  /// gy[4] = -1 analytically, but gy[4] = -0.75 with the cubic function
  double gy[5]  = {0.0, 0.0, 0.0, 0.0,-0.75};
  double gxy[5] = {0, 0, 0, 0, 0};

  test_bicubic(f, d, g, gx, gy, gxy);
}

/**
 * \f[ f = \cos(\pi x)\sin(\pi y)/\pi \f]
 * \f[ f_i = y-y^2-6x^2y+6x^2y^2+4x^3y-4x^3y^2 \f]
 */
void test_bicubic_cossin(void)
{
  double f[16]  = {0, 0, 0, 0, 0, 0, 0, 0, 1,-1, 1,-1, 0, 0, 0, 0};
  double d[16]  = {0, 1,-1, 0, 0, 0, 0, 0, 0,-6, 6, 0, 0, 4,-4, 0};
  double g[5]   = {0, 0, 0, 0, 0};
  /// gx[4] = -1 analytically, but gx[4] = -0.75 with the cubic function
  double gx[5]  = {0.0, 0.0, 0.0, 0.0,-0.75};
  double gy[5]  = {1,-1, 1,-1, 0};
  double gxy[5] = {0, 0, 0, 0, 0};

  test_bicubic(f, d, g, gx, gy, gxy);
}

int main(void)
{
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("bicubic", NULL, NULL);
  CU_add_test(s, "constant", test_bicubic_constant);
  CU_add_test(s, "linear_x", test_bicubic_linear_x);
  CU_add_test(s, "linear_y", test_bicubic_linear_y);
  CU_add_test(s, "sincos",   test_bicubic_sincos);
  CU_add_test(s, "cossin",   test_bicubic_cossin);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
//  CU_console_run_tests();
  CU_cleanup_registry();

  return 0;
}
