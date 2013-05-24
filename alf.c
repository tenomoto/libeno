/// calculates normalized associated Legendre functions
/*
 * @file alf.c
 * @author Takeshi Enomoto
 *
 * source: Belousov (1962) and Swarztrauber (1993)
 * usage: calculates the values of normalized associated Legendre functions
 *        at given latitudes
 * NB. normalised to 1 by default. factor (-1)**m is not included.
 */
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "alf.h"
#include <stdio.h>

static void calc_cd(double c[], double d[], int ntrunc)
{
  c[0] = sqrt(3.0);
  for (int m = 1; m < ntrunc+1; m++) {
    c[m] = sqrt(2.0 * m + 3.0);
    d[m] = sqrt(1.0 + 0.5/m);
  }
}

static void calc_efg(double e[], double f[], double g[], int ntrunc)
{
  int k = 0;
  double n_plus_m, n_minus_m, n2;
  for (int m = 0; m < 2; m++) {
    for (int n = m; n < ntrunc + 1; n++) {
      e[k] = 0.0;
      f[k] = 0.0;
      g[k] = 0.0;
      k++;
    }
  }
  for (int m = 2; m < ntrunc + 1; m++) {
    for (int n = m; n < ntrunc + 1; n++) {
      n_plus_m = n + m;
      n_minus_m = n - m;
      n2 = 2.0 * n;
      g[k] = 1.0 / ((n_plus_m - 1.0) * n_plus_m);
      e[k] = g[k] * (n2 + 1.0) / (n2 - 3.0);
      f[k] = sqrt(e[k] * n_minus_m * (n_minus_m - 1.0));
      e[k] = sqrt(e[k] * (n_plus_m - 2.0) * (n_plus_m - 3.0));
      g[k] = sqrt(g[k] * (n_minus_m + 1.0) * (n_minus_m + 2.0));
      k++;
    }
  }
}

alf_t *eno_alf_init
(
  int ntrunc ///< [in] truncation wave number
)
{
  alf_t *alf;

  alf = (alf_t *)malloc(sizeof(alf_t));
  
  alf->ntrunc = ntrunc;

  int ntrunc1 = ntrunc + 1;
  alf->c = (double *)malloc(sizeof(double)*(ntrunc1));
  alf->d = (double *)malloc(sizeof(double)*(ntrunc1));
  calc_cd(alf->c, alf->d, alf->ntrunc);

  int nn = ntrunc1*(ntrunc1+1)/2;
  alf->e = (double *)malloc(sizeof(double)*nn);
  alf->f = (double *)malloc(sizeof(double)*nn);
  alf->g = (double *)malloc(sizeof(double)*nn);
  calc_efg(alf->e, alf->f, alf->g, alf->ntrunc);

  return alf;
}

void eno_alf_calcps
/// calculates sectional harmonics pmm[1..ntrunc]
  (
    alf_t *alf, ///< [in]  coefficients
    double u,   ///< [in]  coslat
    double ps[] ///< [inout] in: pmm[0], out: pmm[1..ntrunc]
  )
{
  int m;
  int ntrunc1 = alf->ntrunc+1;
  //  calculate while |ps| > DBL_MIN
  for (m = 1; m < ntrunc1 && fabs(ps[m-1]) > DBL_MIN; m++) {
    ps[m] = (alf->d[m]*u)*ps[m-1];
  }
  // fill 0 after |ps| < DBL_MIN
  for (; m < ntrunc1; m++) {
    ps[m] = 0.0;
  }
}

void eno_alf_clean(alf_t *alf)
{
  free(alf->c);
  free(alf->d);
  free(alf->e);
  free(alf->f);
  free(alf->g);
//  free(alf->h);
  free(alf);
}
