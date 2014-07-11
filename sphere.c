/// Functions related to a sphere
/*
 * @file: sphere.c
 * @author: Takeshi Enomoto
 *
 * eno_spherical_helix() generates longitudes \f$\lambda\f$ and
 * colatitudes \f$\theta\f$ of length n with the following equation (Nisho et al 2006).
 * \f[
 *   \lambda = \mod(2k\theta, 2\pi)
 * \f]
 *
 * Here \f$\cos\theta\f$ is equally spaced between \f$-1\f$ and \f$1\f$.
 * NB. Nishio et al. 2006 uses the length of the helix divided by n-1,
 * where n is the number of grid points.
 *
 * # Refereces
 * - Bauer, R., 2000: Distribution of points on a sphere with application to star catalogs. J. Guid. Control. Dyn., 23, 130--137.
 * - Saff, E. B. and A. B. J. Kuijlaars, 1997: Distributing many points on a sphere. Math. Intelligencer, 19, 5--11.
 * - Swinbank, R. and R. J. Purser, 2006: Fibonacci grids: a novel approach to global modelling. 132, 1769--1793.
 */
#include <stdio.h>
#include <math.h>
#include "emath.h"
#include "sphere.h"

double eno_sphere_orthodrome(double lon1, double colat1, double lon2, double colat2) {
  return acos(cos(colat1)*cos(colat2)+sin(colat1)*sin(colat2)*cos(lon1-lon2));
}

int eno_sphere_helix(int n, double *lon, double *colat) {
  double k = sqrt(n*M_PI);

  for (int i=0; i<n; i++) {
    colat[i] = acos(1.0-(2.0*i+1.0)/n);
    lon[i] = eno_emath_mod(k * colat[i], 2*M_PI);
  }
  return 0;
}

int eno_sphere_generalized_spiral(int n, double *lon, double *colat) {
  const double c = 3.6;

  double hk;

  lon[0] = 0.0;
  colat[0] = M_PI;
  for (int k=1; k<n-1; k++) {
    hk = -1.0 + 2.0*k/(n - 1.0);
    colat[k] = acos(hk);
    lon[k] = eno_emath_mod(lon[k-1] + c/sqrt(n*(1.0-hk*hk)), 2*M_PI);
  }
  colat[n-1] = acos(1.0);
  lon[n-1] = 0.0;
  return 0;
}

int eno_sphere_fibonacci(int n, double *lon, double *colat) {
  const double phir = 2.0/(1.0 + sqrt(5.0));

  double m = n*M_PI*phir;
printf("phir = %f m = %f\n", phir, m);
  for (int i=0; i<n; i++) {
    double h = 1.0 - (2.0*i+1.0)/n;
    colat[i] = acos(h);
    lon[i] = eno_emath_mod(-m*h, 2*M_PI);
printf("i = %d h = %f -mh = %f lon = %f\n", i, h, -m*h, lon[i]);
  }
  return 0;
}
