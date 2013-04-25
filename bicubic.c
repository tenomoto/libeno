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
 * p(t,u) = \sum_{i=0}^{3}\sum_{j=0}^{3}a_{ij}x^iy^j
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

void eno_bicubic_coeff /// calculate coeffients from the give function values and the derivatives
  (
    double f[16], /**< [in]  store counter clockwise from the bottom left:
                             (0, 0), (1, 0), (1, 1), (0, 1).
                             f[ 0.. 3] = f,     f[ 4.. 7] = fx*dx,
                             f[ 8..11] = fy*dy, f[12..15] = fxy*dx*dy */
    double c[16]  /**< [out] bicubic coefficients
                   *          0: 1,     1: u,     2: u^2,     3: u^3,
                   *          4: t,     5: tu,    6: tu^2,    7: tu^3
                   *          8: t^2,   9: t^2u, 10: t^2u^2, 11: t^2u^3
                   *         12: t^3u, 13: t^3u, 14: t^3u^2, 15: t^3u^3
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
