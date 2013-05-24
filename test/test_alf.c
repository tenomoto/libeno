#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <math.h>
#include "alf.h"

const int ntrunc = 5;
alf_t *alf;
  
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

void test_alf_ps(void)
{
  const double p00 = sqrt(0.5);
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

  alf = eno_alf_init(ntrunc);
#ifdef VERBOSE
  printf("ntrunc=%d\n", alf->ntrunc);
#endif

  CU_initialize_registry();
  s = CU_add_suite("alf", NULL, NULL);
  CU_add_test(s, "test_cd", test_alf_cd);
  CU_add_test(s, "test_efg", test_alf_cd);
  CU_add_test(s, "test_ps", test_alf_ps);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  eno_alf_clean(alf);

  return 0;
}

