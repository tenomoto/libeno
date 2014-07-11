/// Hybrid sigma-p coordinates
/*
 * @file: sigmap.c
 * @author: Takeshi Enomoto 
 *
 * # Refences
 * - Eckermann (2009) MWR
 * - Ritchie et al. (1994) MWR
 * - Simmons and Burridge (1981) MWR
 */
#include <stdlib.h>
#include <math.h>
#include "air.h"
#include "sigmap.h"

eno_sigmap_t *eno_sigmap_init /// allocate structure and associated arrays
  (
    int n,      /// < [in] # of layers
    double *a,  /// < [in] hybrid A: p
    double *b,  /// < [in] hybrid B: sigma
    double ptop /// < [in] model top pressure (Pa)
  )
{
  eno_sigmap_t *sigmap;
  sigmap = (eno_sigmap_t *)malloc(sizeof(eno_sigmap_t));

  sigmap->n = n;
  sigmap->a = (double *)malloc(sizeof(double) * (n+1));
  sigmap->b = (double *)malloc(sizeof(double) * (n+1));
  sigmap->db = (double *)malloc(sizeof(double) * (n+1));
  for (int i = 0; i < n+1; i++) {
    sigmap->a[i] = a[i];
    sigmap->b[i] = b[i];
  }
  for (int i = 1; i < n+1; i++) {
    sigmap->db[i] = b[i] - b[i-1];
  }
  sigmap->ptop = ptop;
  return sigmap;
}

int eno_sigmap_clean /// deallocate structure and associated arrays
  (
    eno_sigmap_t *sigmap /// < [inout] hybrid sigma-p structure
  )
{
  free(sigmap->a);
  free(sigmap->b);
  free(sigmap->db);
  free(sigmap);
  return 0;
}

int eno_sigmap_calc_p /// calculate half-pressure, layer thickness and full-level pressure
  (
    eno_sigmap_t *sigmap, /// < [in] sigmap structure
    double ps,            /// < [in] surface pressure
    double *ph,           /// < [out] half-level pressure
    double *dp,           /// < [out] layer thickness
    double *pf            /// < [out: full-level pressure
  )
{
  int n = sigmap->n;
  double ptop = sigmap->ptop;
  for (int i = 0; i < n+1; i++) {
    ph[i] = sigmap->a[i] + sigmap->b[i]*(ps - ptop);
  }
  for (int i = 1; i < n+1; i++) {
    dp[i] = ph[i] - ph[i-1];
    pf[i] = 0.5*(ph[i-1]+ph[i]);
  }
  return 0;
}

int eno_sigmap_calc_alphabeta /// calculate alpha and beta from half-level pressure
  (
    eno_sigmap_t *sigmap, /// < [in] sigmap structure
    double *ph,           /// < [in] half-level pressure
    double *dp,           /// < [in] layer thickness
    double *alpha,        /// < [out] alpha
    double *beta          /// < [out] beta
  )
{
  int n = sigmap->n;
  alpha[1] = log(2.0);
  for (int i = 2; i < n+1; i++) {
    beta[i] = log(ph[i]/ph[i-1]);
    alpha[i] = 1.0 -  ph[i-1]/dp[i] * beta[i];
  }
  return 0;
}

int eno_sigmap_calc_gz /// calculate geopotential
 (
  eno_sigmap_t *sigmap, /// < [in] sigmap structure
  double gzs,           /// < [in] surface geopotential
  double *alpha,        /// < [in] alpha
  double *beta,         /// < [in] beta
  double *Tv,           /// < [in] virtual temperature
  double *gz            /// < [out] full-level geopotential
  )
{
  const double Rd = eno_air_Rd;
  int n = sigmap->n;

  double gzh = gzs;
  for (int k = 1; k < n+1; k++) {
    int i = n - k + 1;
    gz[i] = gzh + alpha[i] * Rd * Tv[i];
    gzh = gzh + beta[i] * Rd * Tv[i];
  }
  return 0;
}
  
