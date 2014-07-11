#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "air.h"
#include "earth.h"
#include "sigmap.h"

void test_sigmap(void)
{
  const int n = 2;
  const double ptop = 0.0;
  const double ps =  700.0e2;
  const double Rd = eno_air_Rd;
  const double g = eno_earth_gravity;
  const double gzs =  g*1500.0;

  eno_sigmap_t *sigmap;
  double a[n+1] = {0.0, 0.0, 0.0};
  double b[n+1] = {0.0, 0.5, 1.0}; 
  double ph[n+1];
  double dp[n+1];
  double pf[n+1];
  double alpha[n+1];
  double beta[n+1];
  double Tv[n+1] = {0.0, 220.0, 260.0};
  double gz[n+1];

  sigmap = eno_sigmap_init(n, a, b, ptop);
  CU_ASSERT_EQUAL(sigmap->n, n);
  for (int i=0; i < n+1; i++) {
    CU_ASSERT_EQUAL(sigmap->a[i], a[i]);
    CU_ASSERT_EQUAL(sigmap->b[i], b[i]);
  }
  for (int i=1; i < n+1; i++) {
    CU_ASSERT_EQUAL(sigmap->db[i], 0.5);
  }
  CU_ASSERT_EQUAL(sigmap->ptop, ptop);

  eno_sigmap_calc_p(sigmap, ps, ph, dp, pf);
  for (int i=0; i < n+1; i++) {
    CU_ASSERT_EQUAL(ph[i], a[i] + b[i]*ps);
  }
  for (int i=1; i < n+1; i++) {
    CU_ASSERT_EQUAL(dp[i], 0.5*ps);
    CU_ASSERT_EQUAL(pf[i], 0.5*(ph[i-1]+ph[i]));
  }

  eno_sigmap_calc_alphabeta(sigmap, ph, dp, alpha, beta);
  CU_ASSERT_EQUAL(alpha[1], log(2.0));
  CU_ASSERT_EQUAL(beta[2], log(ph[2]/ph[1]));
  CU_ASSERT_EQUAL(alpha[2], 1.0 - ph[1]/dp[2]*beta[2]);

  eno_sigmap_calc_gz(sigmap, gzs, alpha, beta, Tv, gz);
//  printf("gzs = %f\n", gzs);
//  printf("gz2 = %f %f\n", gz[2], gzs+alpha[2]*Rd*Tv[2]);
  CU_ASSERT_EQUAL(gz[2], gzs+alpha[2]*Rd*Tv[2]);
//  printf("gz1 = %f %f\n", gz[1], gzs+(beta[2]*Tv[2]+alpha[1]*Tv[1])*Rd);
  CU_ASSERT_EQUAL(gz[1], gzs+(beta[2]*Tv[2]+alpha[1]*Tv[1])*Rd);

  eno_sigmap_clean(sigmap);
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("sigmap", NULL, NULL);
  CU_add_test(s, "test_calc_z", test_sigmap);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}

