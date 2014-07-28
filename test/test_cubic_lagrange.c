#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
//#include <CUnit/Console.h>
#include "cubic_lagrange.h"

void test_cubic_lagrange(double xa[4], double ya[4], double g[3])
{
  double t[3] = {0.0, 0.5, 1.0};

  for (int i=0; i<3; i++) {
    CU_ASSERT_EQUAL(eno_cubic_lagrange(xa, ya, t[i]), g[i]);
  }
}

void test_cubic_lagrange_constant(void)
{
  double xa[4] = {-1, 0,    1, 2};
  double ya[4] = { 1, 1,    1, 1};
  double g[3]  = {    1, 1, 1};

  test_cubic_lagrange(xa, ya, g);
}

void test_cubic_lagrange_linear(void)
{
  double xa[4] = {-1, 0,      1, 2};
  double ya[4] = {-1, 0,      1, 2};
  double g[3]  =   {0.0, 0.5, 1.0};

  test_cubic_lagrange(xa, ya, g);
}

/**
 * \f[ y = \cos(\pi x) \f]
 */
void test_cubic_lagrange_cos(void)
{
  double xa[4] = {-1, 0,      1, 2};
  double ya[4] = {-1, 1,     -1, 1};
  double g[3]  = {    1,  0, -1};

  test_cubic_lagrange(xa, ya, g);
}

int main(void)
{
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("bicubic", NULL, NULL);
  CU_add_test(s, "constant", test_cubic_lagrange_constant);
  CU_add_test(s, "linear", test_cubic_lagrange_linear);
  CU_add_test(s, "cos",   test_cubic_lagrange_cos);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
//  CU_console_run_tests();
  CU_cleanup_registry();

  return 0;
}
