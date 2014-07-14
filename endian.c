/// Endian transformation
/**
 * @file endian.c
 * @author Takeshi Enomoto
 *
 */
#include <stdint.h>
#include "endian.h"

float eno_endian_swap_float(float x)
{
  union {
    float x;
    uint32_t i;
  } u;

  u.x = x;
  u.i = SwapConstInt32(u.i);
  return u.x;
}

double eno_endian_swap_double(double x)
{
  union {
    double x;
    uint64_t i;
  } u;

  u.x = x;
  u.i = SwapConstInt64(u.i);
  return u.x;
}
