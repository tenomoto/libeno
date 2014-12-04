#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
/// Extended exponent of floating-point numbers

/*
 * Reference:
 * Fukushima, Toshio, 2011: Numerical computation of spherical
 * harmonics of arbitrary degree and order by extending
 * exponent of floating point numbers. J. Geodesy,
 * doi:10.1007//s00190-011-0519-2
 */

#include "xreal.h"

double eno_xreal_big() { return BIG; }
double eno_xreal_bigi() { return BIGI; }
double eno_xreal_bigs() { return BIGS; }
double eno_xreal_bigsi() { return BIGSI; }

void eno_xreal_norm(xreal_t *x)
{
  double w = fabs(x->p);
  if (w >= BIGS) {
    x->p *= BIGI;
    ++x->i;
  } else if (w < BIGSI) {
    x->p *= BIG;
    --x->i;
  }
}

void eno_xreal_assign_f(double f, xreal_t *x)
{
  x->p = f;
  x->i = 0;
}

void eno_xreal_assign_x(xreal_t x, xreal_t *y)
{
  y->p = x.p;
  y->i = x.i;
  eno_xreal_norm(y);
}

double eno_xreal_eval(xreal_t x)
{
  eno_xreal_norm(&x);
  if (x.i == 0) {
    return x.p;
  } else if (x.i < 0) { // underflow
    return x.p * BIGI;
  } else {            // overflow i > 0
    return x.p * BIG;
  }
}

void eno_xreal_fxpgy(double f, xreal_t x, double g, xreal_t y, xreal_t *z)
{
  int id = x.i - y.i;

  if (id == 0) {
    z->p = f * x.p + g * y.p;
    z->i = x.i;
  } else if (id == 1) {
    z->p = f * x.p + g * BIGI * y.p;
    z->i = x.i;
  } else if (id == -1) {
    z->p = f * BIGI * x.p + g * y.p;
    z->i = y.i;
  } else if (id > 1) {
    z->p = f * x.p;
    z->i = x.i;
  } else { // id < 1
    z->p = g * y.p;
    z->i = y.i;
  }
  eno_xreal_norm(z);
}

void eno_xreal_mul(xreal_t x, xreal_t y, xreal_t *z)
{
  xreal_t s;

  eno_xreal_assign_x(x, z);
  eno_xreal_norm(z);
  eno_xreal_assign_x(y, &s);
  eno_xreal_norm(&s);
  z->p = z->p * s.p;
  z->i = z->i + s.i;
  eno_xreal_norm(z);
}

void eno_xreal_fx(double f, xreal_t x, xreal_t *y)
{
  eno_xreal_norm(&x);
  y->p = f * x.p;
  y->i = x.i;
  eno_xreal_norm(y);
}

void eno_xreal_div(xreal_t x, xreal_t y, xreal_t *z)
{
  xreal_t s;

  eno_xreal_assign_x(x, z);
  eno_xreal_norm(z);
  eno_xreal_assign_x(y, &s);
  eno_xreal_norm(&s);
  z->p = z->p / s.p;
  z->i = z->i - s.i;
  eno_xreal_norm(z);
}

void eno_xreal_fxr(double f, xreal_t x, xreal_t *y)
{
  eno_xreal_norm(&x);
  y->p = f / x.p;
  y->i = x.i;
  eno_xreal_norm(y);
}

void eno_xreal_ipow(xreal_t x, int n, xreal_t *y)
{
  xreal_t z;

  eno_xreal_assign_f(1.0, y);
  eno_xreal_assign_x(x, &z);
  eno_xreal_norm(&z);
  if (n < 0) {
    eno_xreal_fxr(1.0, x, &z);
    n = -n;
  }
  do {
    if (n & 1) {
      eno_xreal_mul(*y, z, y);
    }
    n >>= 1;
    eno_xreal_mul(z, z, &z);
  } while (n);
  eno_xreal_norm(y);
}

void eno_xreal_add(xreal_t x, xreal_t y, xreal_t *z)
{
  eno_xreal_fxpgy(1.0, x, 1.0, y, z);
}

void eno_xreal_sub(xreal_t x, xreal_t y, xreal_t *z)
{
  eno_xreal_fxpgy(1.0, x, -1.0, y, z);
}

bool eno_xreal_eq(xreal_t x, xreal_t y)
{
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  return (x.p == y.p) && (x.i == y.i);
}

bool eno_xreal_ne(xreal_t x, xreal_t y)
{
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  return (x.p != y.p) || (x.i != y.i);
}

bool eno_xreal_gt(xreal_t x, xreal_t y)
{
  bool l;
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  if (x.i == y.i) {
    l = x.p > y.p;
  } else {
    l = x.i > y.i;
  }
  if (x.p * y.p < 0) {
    l = !l;
  }
  return l;
}

bool eno_xreal_ge(xreal_t x, xreal_t y)
{
  bool l;
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  if (x.i == y.i) {
    l = x.p >= y.p;
  } else {
    l = x.i >= y.i;
  }
  if (x.p * y.p < 0) {
    l = !l;
  }
  return l;
}

bool eno_xreal_lt(xreal_t x, xreal_t y)
{
  bool l;
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  if (x.i == y.i) {
    l = x.p < y.p;
  } else {
    l = x.i < y.i;
  }
  if (x.p * y.p < 0) {
    l = !l;
  }
  return l;
}

bool eno_xreal_le(xreal_t x, xreal_t y)
{
  bool l;
  eno_xreal_norm(&x);
  eno_xreal_norm(&y);
  if (x.i == y.i) {
    l = x.p <= y.p;
  } else {
    l = x.i <= y.i;
  }
  if (x.p * y.p < 0) {
    l = !l;
  }
  return l;
}

void eno_xreal_base10(xreal_t x, xreal_t *y)
{
  int i10 = lround(log10(BIG));
  double p10 = BIG * ipow(10.0, -i10);

  y->p = x.p;
  y->i = x.i;
  if (x.i != 0) {
    y->i = lround(log10(fabs(x.p)));
    y->p = (x.p * ipow(10.0, -y->i)) * ipow(p10, x.i);
    y->i = y->i + i10 * x.i;
  }
}
