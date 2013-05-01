///  Bicubic interpolation
/**
 * @file bicubic.c
 * @author Takeshi Enomoto
 *
 * # Algorithm
 *
 * Given the function values \f$f\f$ and its derivatives \f$f_x\f$, \f$f_y\f$ and \f$f_{xy}\f$
 * at four corners, the interpolated surface is given by
 * \f[
 * p(t,u) = \sum_{i=0}^{3}\sum_{j=0}^{3}a_{ij}t^iu^j
 * \f]
 * The given function values and the derivatives matches those of the interpolated surface
 * at four corners to determine 16 coefficients.
 *
 * # Reference
 *
 * - [Numerical Recepies in C](http://www.nrbook.com/a/bookcpdf.php): 
 *   [3.6 Interpolation in Two or More Dimensions](http://www.nrbook.com/a/bookcpdf/c3-6.pdf)
 * - [Bicubic Interpolation](http://en.wikipedia.org/wiki/Bicubic)
 *  
 */
#include "bicubic.h"

/// calculate coeffients from the give function values and the derivatives
void eno_bicubic_coeff
  (
    double f[16], /**< [in]  store counter clockwise from the bottom left:
                             (0, 0), (1, 0), (1, 1), (0, 1).
                             f[ 0.. 3] = \f$f\f$,
                             f[ 4.. 7] = \f$f_x\Delta x\f$,
                             f[ 8..11] = \f$f_y\Delta y\f$,
                             f[12..15] = \f$f_{xy}\Delta x\Delta dy\f$
                   */
    double c[16]  /**< [out] bicubic coefficients
                   *          0: \f$1\f$,     1: \f$u\f$,     2: \f$u^2\f$,     3: \f$u^3\f$,
                   *          4: \f$t\f$,     5: \f$tu\f$,    6: \f$tu^2\f$,    7: \f$tu^3\f$,
                   *          8: \f$t^2\f$,   9: \f$t^2u\f$, 10: \f$t^2u^2\f$, 11: \f$t^2u^3\f$,
                   *         12: \f$t^3u\f$, 13: \f$t^3u\f$, 14: \f$t^3u^2\f$, 15: \f$t^3u^3\f$
                   */
  )
{
  double a[16*16] = {
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
-3, 0, 0, 3, 0, 0, 0, 0,-2, 0, 0,-1, 0, 0, 0, 0,
 2, 0, 0,-2, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
 0, 0, 0, 0,-3, 0, 0, 3, 0, 0, 0, 0,-2, 0, 0,-1,
 0, 0, 0, 0, 2, 0, 0,-2, 0, 0, 0, 0, 1, 0, 0, 1,
-3, 3, 0, 0,-2,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,-3, 3, 0, 0,-2,-1, 0, 0,
 9,-9, 9,-9, 6, 3,-3,-6, 6,-6,-3, 3, 4, 2, 1, 2,
-6, 6,-6, 6,-4,-2, 2, 4,-3, 3, 3,-3,-2,-1,-1,-2,
 2,-2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 2,-2, 0, 0, 1, 1, 0, 0,
-6, 6,-6, 6,-3,-3, 3, 3,-4, 4, 2,-2,-2,-2,-1,-1,
 4,-4, 4,-4, 2, 2,-2,-2, 2,-2,-2, 2, 1, 1, 1, 1
};

    for (int i = 0; i < 16; i++) {
      c[i] = 0.0;
      for (int j = 0; j < 16; j++) {
        c[i] = c[i] + a[16*i+j] * f[j];
      }
    }
}

double eno_bicubic_interpolate /// interpolate at (t,u) using c[]
  (
    double c[16], ///< [in] coefficents obtained by eno_bicubic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=3; i>=0; i--) {
      fi = t*fi+((c[4*i+3]*u+c[4*i+2])*u+c[4*i+1])*u+c[4*i];
  }
  return fi;
}

double eno_bicubic_interpolate_x /// interpolate x-derivative at (t,u) using c[]
  (
    double c[16], ///< [in] coefficents obtained by eno_bicubic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=3; i>=1; i--) {
      fi = t*fi+i*(((c[4*i+3]*u+c[4*i+2])*u+c[4*i+1])*u+c[4*i]);
  }
  return fi;
}

double eno_bicubic_interpolate_y /// interpolate y-derivative at (t,u) using c[]
  (
    double c[16], ///< [in] coefficents obtained by eno_bicubic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=3; i>=0; i--) {
      fi = t*fi+(3.0*c[4*i+3]*u+2.0*c[4*i+2])*u+c[4*i+1];
  }
  return fi;
}

double eno_bicubic_interpolate_xy /// interpolate xy-derivative at (t,u) using c[]
  (
    double c[16], ///< [in] coefficents obtained by eno_bicubic_coeff()
    double t,     ///< [in] desired point in \f$x\f$
    double u      ///< [in] desired point in \f$y\f$
  )
{
  double fi = 0.0;

  for (int i=3; i>=1; i--) {
      fi = t*fi+i*((3.0*c[4*i+3]*u+2.0*c[4*i+2])*u+c[4*i+1]);
  }
  return fi;
}
