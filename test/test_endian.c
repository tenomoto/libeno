#include <stdio.h>
#include <stdint.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "endian.h"

void test_endian_float(void)
{
  FILE *f;
  float x = 32.0;
  float y, z;

  f = fopen("test_endian.dat","wb");
  fwrite(&x, sizeof(float), 1, f);
  fclose(f);
  f = fopen("test_endian.dat","rb");
  fread(&y, sizeof(float), 1, f);
  fclose(f);
  printf("x=%f, y=%f\n",x,y);
  CU_ASSERT_EQUAL(x, y);

  z = eno_endian_swap_float(x);
  f = fopen("test_endian.dat","wb");
  fwrite(&z, sizeof(float), 1, f);
  fclose(f);
  f = fopen("test_endian.dat","rb");
  fread(&y, sizeof(float), 1, f);
  y = eno_endian_swap_float(y);
  printf("x=%f, y=%f\n",x,y);
  CU_ASSERT_EQUAL(x, y);
}

int main(void) {
  CU_pSuite s;

  CU_initialize_registry();
  s = CU_add_suite("endian", NULL, NULL);
  CU_add_test(s, "float", test_endian_float);
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return 0;
}
