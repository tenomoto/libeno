#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include "xreal.h"

void  test_xreal()
{
  double xp, yp, zp, wp, vp;
  int   xi, yi, zi, wi, vi;

  printf("----- xreal_test() -----\n");

  printf("big=%e\n", eno_xreal_big());
  printf("bigi=%e\n", eno_xreal_bigi());
  printf("bigs=%e\n", eno_xreal_bigs());
  printf("bigsi=%e\n", eno_xreal_bigsi());

  double f = 3.0e100;
  double g = 5.0e99;
  xp = f;
  xi = 0;
  yp = g;
  yi = 0;
  printf("f=%e xp=%e xi=%d, g=%e, yp=%e yi=%d\n", f, xp, xi, g, yp, yi);

  eno_xreal_mul(xp, xi, yp, yi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("x*y=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_add(xp, xi, yp, yi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("x+y=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_sub(xp, xi, yp, yi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("x-y=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_div(xp, xi, yp, yi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("x/y=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_fxpgy(f, xp, xi, g, yp, yi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("fx+gy=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_mul(xp, xi, xp, xi, &zp, &zi);
  eno_xreal_mul(zp, zi, xp, xi, &zp, &zi);
  eno_xreal_mul(zp, zi, xp, xi, &zp, &zi);
  eno_xreal_mul(zp, zi, xp, xi, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("x*x*x*x*x=%e %d %e %d\n", zp, zi, wp, wi);
  eno_xreal_ipow(xp, xi, 5, &zp, &zi);
  eno_xreal_base10(zp, zi, &vp, &vi);
  printf("pow(x,5)=%e %d %e %d\n", zp, zi, vp, vi);
  printf("wp - vp=%e wi-vi=%d\n", wp-vp, wi-vi);
  CU_ASSERT_EQUAL(wp, vp)
  CU_ASSERT_EQUAL(wi, vi)

  eno_xreal_ipow(xp, xi, -2, &zp, &zi);
  eno_xreal_base10(zp, zi, &wp, &wi);
  printf("pow(x,-2)=%e %d %e %d\n", zp, zi, wp, wi);

  eno_xreal_ipow(xp, xi, 3, &zp, &zi);
  printf("x**3==y %d\n", eno_xreal_eq(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_eq(zp, zi, yp, yi), false);
  printf("x**3/=y %d\n", eno_xreal_ne(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_ne(zp, zi, yp, yi), true);
  printf("x**3>y %d\n", eno_xreal_gt(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_gt(zp, zi, yp, yi), true);
  printf("x**3>=y %d\n", eno_xreal_ge(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_ge(zp, zi, yp, yi), true);
  printf("x**3>=x**3 %d\n", eno_xreal_ge(zp, zi, zp, zi));
  CU_ASSERT_EQUAL(eno_xreal_ge(zp, zi, zp, zi), true);
  printf("x**3<y %d\n", eno_xreal_lt(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_lt(zp, zi, yp, yi), false);
  printf("x**3<=y %d\n", eno_xreal_le(zp, zi, yp, yi));
  CU_ASSERT_EQUAL(eno_xreal_le(zp, zi, yp, yi), false);
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("xreal", NULL, NULL);
  CU_add_test(s, "test", test_xreal);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

