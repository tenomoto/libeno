#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xreal.h"

void  test_xreal()
{
  xreal_t x, y, z, w, v;

  printf("----- xreal_test() -----\n");

  printf("big=%e\n", eno_xreal_big());
  printf("bigi=%e\n", eno_xreal_bigi());
  printf("bigs=%e\n", eno_xreal_bigs());
  printf("bigsi=%e\n", eno_xreal_bigsi());

  double f = 3.0e100;
  double g = 5.0e99;
  eno_xreal_assign_f(f, &x);
  eno_xreal_assign_f(g, &y);
  printf("f=%e x.p=%e x.i=%d, g=%e, y.p=%e y.i=%d\n", f, x.p, x.i, g, y.p, y.i);

  eno_xreal_norm(&x);

  eno_xreal_mul(x, y, &z);
  eno_xreal_base10(z, &w);
  printf("x*y=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_add(x, y, &z);
  eno_xreal_base10(z, &w);
  printf("x+y=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_sub(x, y, &z);
  eno_xreal_base10(z, &w);
  printf("x-y=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_div(x, y, &z);
  eno_xreal_base10(z, &w);
  printf("x/y=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_fxpgy(f, x, g, y, &z);
  eno_xreal_base10(z, &w);
  printf("fx+gy=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_mul(x, x, &z);
  eno_xreal_mul(z, x, &z);
  eno_xreal_mul(z, x, &z);
  eno_xreal_mul(z, x, &z);
  eno_xreal_base10(z, &w);
  printf("x*x*x*x*x=%e %d %e %d\n", z.p, z.i, w.p, w.i);
  eno_xreal_ipow(x, 5, &z);
  eno_xreal_base10(z, &v);
  printf("pow(x,5)=%e %d %e %d\n", z.p, z.i, v.p, v.i);
  printf("wp-vp=%e wi-vi=%d\n", w.p-v.p, w.i-v.i);
  CU_ASSERT_EQUAL(w.p, v.p)
  CU_ASSERT_EQUAL(w.i, v.i)

  eno_xreal_ipow(x, -2, &z);
  eno_xreal_base10(z, &w);
  printf("pow(x,-2)=%e %d %e %d\n", z.p, z.i, w.p, w.i);

  eno_xreal_ipow(x, 3, &z);
  printf("x**3==y %d\n", eno_xreal_eq(z, y));
  CU_ASSERT_EQUAL(eno_xreal_eq(z, y), false);
  printf("x**3/=y %d\n", eno_xreal_ne(z, y));
  CU_ASSERT_EQUAL(eno_xreal_ne(z, y), true);
  printf("x**3>y %d\n", eno_xreal_gt(z, y));
  CU_ASSERT_EQUAL(eno_xreal_gt(z, y), true);
  printf("x**3>=y %d\n", eno_xreal_ge(z, y));
  CU_ASSERT_EQUAL(eno_xreal_ge(z, y), true);
  printf("x**3>=x**3 %d\n", eno_xreal_ge(z, z));
  CU_ASSERT_EQUAL(eno_xreal_ge(z, z), true);
  printf("x**3<y %d\n", eno_xreal_lt(z, y));
  CU_ASSERT_EQUAL(eno_xreal_lt(z, y), false);
  printf("x**3<=y %d\n", eno_xreal_le(z, y));
  CU_ASSERT_EQUAL(eno_xreal_le(z, y), false);
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

