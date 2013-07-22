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
 * - Nishio, H., M. Altaf-Ul-Amin, K. Kurokawa, K. and S. Kanaya, 2006: Spherical SOM and arrangement of neurons using helix on sphere. IPSJ Digital Courier, 2, 133--137.
 */
#include <math.h>
#include "sphere.h"

double eno_sphere_orthodrome(double lon1, double colat1, double lon2, double colat2) {
  return acos(cos(colat1)*cos(colat2)+sin(colat1)*sin(colat2)*cos(lon1-lon2));
}

int eno_sphere_helix(int n, double *lon, double *colat) {
  double k = sqrt(n);
  double d = 2.0/(n-1);
  double pi2 = 2.0*M_PI;
  for (int i=0; i<n; i++) {
    colat[i] = acos(-1.0+i*d);
    lon[i] = fmod(2.0 * k * colat[i], pi2);
  }
  return 0;
}
