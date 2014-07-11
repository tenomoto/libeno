///  Biquadratic interpolation
/**
 * @file biquadratic.c
 * @author Takeshi Enomoto
 *
 * # Algorithm
 *
 * Given the function values \f$f\f$ at four corners, mid-points of vertices
 * and the cell centre * the interpolated surface is given by
 * \f[
 * p(t,u) = \sum_{i=0}^{2}\sum_{j=0}^{2}a_{ij}t^iu^j
 * \f]
 * The given function values matches those of the interpolated surface
 * at four corners, middle points and cell centre to determine 9 coefficients.
 *
 * # Reference
 *
 * - [What's the point? Interpolation and extrapolation with a regular grid DEM](http://www.geocomputation.org/1999/082/gc_082.htm)
 *  
 */
#include "biquadratic.h"

/// calculate coeffients from the give function values and the derivatives
void eno_biquadratic_coeff
  (
    double f[9], /**< [in]  store counter clockwise from the bottom left:
                             (0, 0),   (0.5, 0), (1, 0),
                             (1, 0.5), (1, 1),   (0.5, 1),
                             (0, 1),   (0, 0.5), (0.5, 0.5)
                   */
    double c[9]  /**< [out] biquadratic coefficients
                   *          0: \f$1\f$,     1: \f$u\f$,     2: \f$u^2\f$,
                   *          3: \f$t\f$,     4: \f$tu\f$,    5: \f$tu^2\f$,
                   *          6: \f$t^2\f$,   7: \f$t^2u\f$,  8: \f$t^2u^2\f$
                   */
  )
{
  double a[9*9] = {
     1,   0,   0,   0,   0,   0,   0,   0,   0,
    -3,   0,   0,   0,   0,   0,  -1,   4,   0,
     2,   0,   0,   0,   0,   0,   2,  -4,   0,
    -3,   4,  -1,   0,   0,   0,   0,   0,   0,
     9, -12,   3,  -4,   1,  -4,   3, -12,  16,
    -6,   8,  -2,   4,  -2,   8,  -6,  12, -16,
     2,  -4,   2,   0,   0,   0,   0,   0,  -0,
    -6,  12,  -6,   8,  -2,   4,  -2,   8, -16,
     4,  -8,   4,  -8,   4,  -8,   4,  -8,  16
};

    for (int i = 0; i < 9; i++) {
      c[i] = 0.0;
      for (int j = 0; j < 9; j++) {
        c[i] = c[i] + a[9*i+j] * f[j];
      }
    }
}

double eno_biquadratic_interpolate /// interpolate at (t,u) using c[]
  (
    double c[9],  ///< [in] coefficents obtained by eno_quadratic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=2; i>=0; i--) {
      fi = t*fi+(c[3*i+2]*u+c[3*i+1])*u+c[3*i];
  }
  return fi;
}

double eno_biquadratic_interpolate_x /// interpolate x-derivative at (t,u) using c[]
  (
    double c[9],  ///< [in] coefficents obtained by eno_biquadratic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=2; i>=1; i--) {
      fi = t*fi+i*((c[3*i+2]*u+c[3*i+1])*u+c[3*i]);
  }
  return fi;
}

double eno_biquadratic_interpolate_y /// interpolate y-derivative at (t,u) using c[]
  (
    double c[9],  ///< [in] coefficents obtained by eno_biquadratic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=2; i>=0; i--) {
      fi = t*fi+2.0*c[3*i+2]*u+c[3*i+1];
  }
  return fi;
}

double eno_biquadratic_interpolate_xy /// interpolate xy-derivative at (t,u) using c[]
  (
    double c[9],  ///< [in] coefficents obtained by eno_biquadratic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=2; i>=1; i--) {
      fi = t*fi+i*(2.0*c[3*i+2]*u+c[3*i+1]);
  }
  return fi;
}
