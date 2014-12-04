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

double eno_xreal_big()
{
    return BIG;
}

double eno_xreal_bigi()
{
    return BIGI;
}

double eno_xreal_bigs()
{
    return BIGS;
}

double eno_xreal_bigsi()
{
    return BIGSI;
}
 
void eno_xreal_norm(double *p, int *i)
{
  double w = fabs(*p);
  if (w >= BIGS) {
    *p *= BIGI;
    ++*i;
  } else if (w < BIGSI) {
    *p *= BIG;
    --*i;
  }
}

void eno_xreal_assign_f(double f, double *p, int *i)
{
  *p = f;
  *i = 0;
}

void eno_xreal_assign_x(double xp, int xi, double *yp, int *yi)
{
  *yp = xp;
  *yi = xi;
  eno_xreal_norm(yp, yi);
}

double eno_xreal_eval(double p, int i)
{
  if (i == 0) {
    return p;
  } else if (i < 0) { // underflow
    return p * BIGI;
  } else {            // overflow i > 0
    return p * BIG;
  }
}

void eno_xreal_fxpgy
(
  double f,
  double xp, int xi,
  double g,
  double yp, int yi,
  double *zp, int *zi)
{
  int id = xi - yi;
  if (id == 0) {
    *zp = f * xp + g * yp;
    *zi = xi;
  } else if (id == 1) {
    *zp = f * xp + g * BIGI * yp;
    *zi = xi;
  } else if (id == -1) {
    *zp = f * BIGI * xp + g * yp;
    *zi = yi;
  } else if (id > 1) {
    *zp = f * xp;
    *zi = xi;
  } else { // id < 1
    *zp = g * yp;
    *zi = yi;
  }
  eno_xreal_norm(zp, zi);
}

void eno_xreal_mul(double xp, int xi, double yp, int yi, double *zp, int *zi)
{
  double sp; int si;

  eno_xreal_assign_x(xp, xi, zp, zi);
  eno_xreal_norm(zp, zi);
  eno_xreal_assign_x(yp, yi, &sp, &si);
  eno_xreal_norm(&sp, &si);
  *zp = *zp * sp;
  *zi = *zi + si;
  eno_xreal_norm(zp, zi);
}

void eno_xreal_fx(double f, double xp, int xi, double *zp, int *zi)
{
  eno_xreal_norm(&xp, &xi);
  *zp = f * xp;
  *zi = xi;
  eno_xreal_norm(zp, zi);
}

void eno_xreal_div(double xp, int xi, double yp, int yi, double *zp, int *zi)
{
  double sp; int si;

  eno_xreal_assign_x(xp, xi, zp, zi);
  eno_xreal_norm(zp, zi);
  eno_xreal_assign_x(yp, yi, &sp, &si);
  eno_xreal_norm(&sp, &si);
  *zp = *zp / sp;
  *zi = *zi - si;
  eno_xreal_norm(zp, zi);
}

void eno_xreal_fxr(double f, double xp, int xi, double *yp, int *yi)
{
  eno_xreal_norm(&xp, &xi);
  *yp = f / xp;
  *yi = xi;
  eno_xreal_norm(yp, yi);
}

void eno_xreal_ipow(double xp, int xi, int n, double *yp, int *yi)
{
  double f = 1.0;
  double zp; int zi;

  eno_xreal_assign_f(1.0, yp, yi);
  eno_xreal_assign_x(xp, xi, &zp, &zi);
  eno_xreal_norm(&zp, &zi);
  if (n < 0) {
    eno_xreal_fxr(f, xp, xi, &zp, &zi);
    n = -n;
  }
  do {
    if (n & 1) {
      eno_xreal_mul(*yp, *yi, zp, zi, yp, yi);
    }
    n >>= 1;
    eno_xreal_mul(zp, zi, zp, zi, &zp, &zi);
  } while (n);
  eno_xreal_norm(yp, yi);
}

void eno_xreal_add(double xp, int xi, double yp, int yi, double* zp, int *zi)
{
  eno_xreal_fxpgy(1.0, xp, xi, 1.0, yp, yi, zp, zi);
}

void eno_xreal_sub(double xp, int xi, double yp, int yi, double* zp, int *zi)
{
  eno_xreal_fxpgy(1.0, xp, xi, -1.0, yp, yi, zp, zi);
}

bool eno_xreal_eq(double xp, int xi, double yp, int yi)
{
  eno_xreal_norm(&xp, &xi);
  eno_xreal_norm(&yp, &yi);
  return (xp == yp) && (xi == yi);
}

bool eno_xreal_ne(double xp, int xi, double yp, int yi)
{
  eno_xreal_norm(&xp, &xi);
  eno_xreal_norm(&yp, &yi);
  return (xp != yp) || (xi != yi);
}

bool eno_xreal_gt(double xp, int xi, double yp, int yi)
{
  bool l;
  if (xi == yi) {
    l = xp > yp;
  } else {
    l = xi > yi;
  }
  if (xp * yp < 0) {
    l = !l;
  }
  return l;
}

bool eno_xreal_ge(double xp, int xi, double yp, int yi)
{
  bool l;
  if (xi == yi) {
    l = xp >= yp;
  } else {
    l = xi >= yi;
  }
  if (xp * yp < 0) {
    l = !l;
  }
  return l;
}


bool eno_xreal_lt(double xp, int xi, double yp, int yi)
{
  bool l;
  if (xi == yi) {
    l = xp < yp;
  } else {
    l = xi < yi;
  }
  if (xp * yp < 0) {
    l = !l;
  }
  return l;
}

bool eno_xreal_le(double xp, int xi, double yp, int yi)
{
  bool l;
  if (xi == yi) {
    l = xp <= yp;
  } else {
    l = xi <= yi;
  }
  if (xp * yp < 0) {
    l = !l;
  }
  return l;
}

void eno_xreal_base10(double xp, int xi, double *yp, int *yi)
{
  int i10 = lround(log10(BIG));
  double p10 = BIG * ipow(10.0, -i10);

  *yp = xp;
  *yi = xi;
  if (xi != 0) {
    *yi = lround(log10(fabs(xp)));
    *yp = (xp * ipow(10.0, -*yi)) * ipow(p10, xi);
    *yi = *yi + i10 * xi;
  }
}
