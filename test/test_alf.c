#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <math.h>
#include "alf.h"

const int ntrunc = 5;
double p00;
eno_alf_t *alf;
  
void test_alf_cd(void)
{
#ifdef VERBOSE
  printf("\n%d %f\n", 0, alf->c[0]);
#endif
  CU_ASSERT_EQUAL(sqrt(3.0), alf->c[0]);
  for (int m = 1; m < ntrunc+1; m++) {
#ifdef VERBOSE
    printf("%d %f %f\n", m, alf->c[m], alf->d[m]);
#endif
    CU_ASSERT_EQUAL(sqrt(2.0 * m + 3.0),alf->c[m]);
    CU_ASSERT_EQUAL(sqrt(1.0 + 0.5/m), alf->d[m]);
  }
}

void test_alf_efg(void) {

  int k = 0;
  double e, f, g;

#ifdef VERBOSE
  printf("\n");
#endif
  for (int m = 0; m < 2; m++) {
    for (int n = m; n < ntrunc+1; n++) {
      k++;
    }
  }
  for (int m = 2; m < ntrunc + 1; m++) {
    for (int n = m; n < ntrunc + 1; n++) {
      g = 1.0 / ((n+m-1.0)*(n+m));
      e = g*(2*n+1.0)/(2*n-3.0);
      f = sqrt(e*(n-m)*(n-m-1.0));
      e = sqrt(e*(n+m-2.0)*(n+m-3.0));
      g = sqrt(g*(n-m+1.0)*(n-m+2.0));
#ifdef VERBOSE
      printf("%d (%d %d): %f %f %f %f %f %f\n", k, m, n, e, alf->e[k], f, alf->f[k], g, alf->g[k]);
#endif
      CU_ASSERT_EQUAL(e, alf->e[k]);
      CU_ASSERT_EQUAL(f, alf->f[k]);
      CU_ASSERT_EQUAL(g, alf->g[k]);
      k++;
    }
  }
}

void test_alf_ank(void) {
  double ank[5];
  
  ank[0] = 2.0 * p00; // a0,0
  ank[1] = sqrt(3.0) * p00; // a1,0
  ank[2] = 0.75 * sqrt(5.0) * p00; // a2,2
//  ank[3] = 0.25 * sqrt(5.0) * p00; // a2,0
  ank[3] = ank[2]/3.0; // a2,0
//  ank[4] = 0.625 * sqrt(7.0) * p00; // a3,3
  ank[4] = sqrt(35.0/36.0) * ank[2]; // a3,3
#ifdef VERBOSE
  printf("\n");
  for (int i=0; i < 5; i++) {
    printf("%d %20.18f %20.18f %20.18f\n", i, alf->ank[i], ank[i], alf->ank[i]-ank[i]);
  }
#endif
  CU_ASSERT_EQUAL(alf->ank[0], ank[0]);
  CU_ASSERT_EQUAL(alf->ank[1], ank[1]);
  CU_ASSERT_EQUAL(alf->ank[2], ank[2]);
  CU_ASSERT_EQUAL(alf->ank[3], ank[3]);
  CU_ASSERT_EQUAL(alf->ank[4], ank[4]);
}

void test_alf_ps(void)
{
  double u = 0.5;
  double ps[ntrunc];

  ps[0] = p00;
#ifdef VERBOSE
  printf("\n%d %f\n", 0, ps[0]);
#endif
  CU_ASSERT_EQUAL(p00, ps[0]);
  eno_alf_calcps(alf, u, ps);
  for (int m = 1; m < ntrunc+1; m++) {
#ifdef VERBOSE
    printf("%d %f\n", m, ps[m]);
    CU_ASSERT_EQUAL(sqrt(1.0 + 0.5/m)*u*ps[m-1], ps[m]);
#endif
  }
}

int main(void) {
  CU_pSuite s;
  
  p00 = sqrt(0.5);
  alf = eno_alf_init(ntrunc, p00);
#ifdef VERBOSE
  printf("ntrunc=%d\n", alf->ntrunc);
#endif

  CU_initialize_registry();
  s = CU_add_suite("alf", NULL, NULL);
  CU_add_test(s, "test_cd", test_alf_cd);
  CU_add_test(s, "test_efg", test_alf_efg);
  CU_add_test(s, "test_ank", test_alf_ank);
  CU_add_test(s, "test_ps", test_alf_ps);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  eno_alf_clean(alf);

  return 0;
}

