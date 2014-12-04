/// Functions to calculate normalized associated Legendre functions
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

/// calculates c, d for diagonal starting values
static void calc_cd(double c[], double d[], int ntrunc)
{
  c[0] = sqrt(3.0);
  for (int m = 1; m < ntrunc + 1; m++) {
    c[m] = sqrt(2.0 * m + 3.0);
    d[m] = sqrt(1.0 + 0.5/m);
  }
}

/// calculates e, f, g in the four-point recurrence
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

/// calculates Fourier coefficients
static void calc_ank(double p0, double ank[], int ntrunc)
{
  ank[0] = 2.0 * p0;
  ank[1] = sqrt(3.0) * p0; // sqrt(1-1/4) * 2 * p0
  int i = 2;
  for (int n = 2; n < ntrunc + 1; n++) {
    int np = (n - 1) / 2 + 1;
    int nh = n / 2;
    ank[i] = sqrt(1.0 - 1.0 / (4.0 * n * n)) * ank[i - np];
    i++;
    for (int lh = 1; lh < nh + 1; lh++) {
      int l = 2 * lh;
      int n2l = 2 * n - l;
      ank[i] = (l - 1.0)*(n2l + 2.0) / (l * (n2l + 1.0)) * ank[i - 1];
      i++;
    }
    if (n == nh*2) { // a(n,0) coefficient of $\cos 0\theta$ is halved
      ank[i - 1] = 0.5 * ank[i - 1];
    }
  }
}

eno_alf_t *eno_alf_init
(
  int ntrunc, ///< [in] truncation wave number
  double p00  ///< [in] start value affecting normalization
)
{
  eno_alf_t *alf;

  alf = (eno_alf_t *)malloc(sizeof(eno_alf_t));
  
  alf->ntrunc = ntrunc;
  alf->p00 = p00;

  int ntrunc1 = ntrunc + 1;
  alf->c = (double *)malloc(sizeof(double) * ntrunc1);
  alf->d = (double *)malloc(sizeof(double) * ntrunc1);
  calc_cd(alf->c, alf->d, alf->ntrunc);

  int nn = ntrunc1 * (ntrunc1 + 1) / 2;
  alf->e = (double *)malloc(sizeof(double) * nn);
  alf->f = (double *)malloc(sizeof(double) * nn);
  alf->g = (double *)malloc(sizeof(double) * nn);
  calc_efg(alf->e, alf->f, alf->g, alf->ntrunc);

  int nh = ntrunc / 2;
  alf->ank = (double *)malloc(sizeof(double) * (nh + 2) * (nh + 1));
  calc_ank(p00, alf->ank, ntrunc);

  return alf;
}

void eno_alf_calcps
/// calculates sectional harmonics pmm[1..ntrunc]
  (
    eno_alf_t *alf, ///< [in]  coefficients
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

void eno_alf_clean(eno_alf_t *alf)
{
  free(alf->c);
  free(alf->d);
  free(alf->e);
  free(alf->f);
  free(alf->g);
  free(alf->ank);
  free(alf);
}
