/// Cubic Hermite interpolation
/**
 * @file cubic_hermite.c
 * @author Takeshi Enomoto
 *
 * # Algorithm
 *
 * Given the function values \f$f\f$ and its derivative \f$f_x\f$,
 * at two points, the interpolated curve is given by
 * \f[
 * p(t) = \sum_{i=0}^{3}a_{i}t^i
 * \f]
 * The given function values and the derivatives matches those of the interpolated curve
 * at two points to determine 4 coefficients.
 * Cubic Hermite interpolation is an 1D version of bicubic interpolation.
 *
 * # Reference
 *
 * - [Cubic Hermite spline](http://en.wikipedia.org/wiki/Cubic_Hermite_spline)
 * - [Hermite Curve Interpolation](http://www.cubic.org/docs/hermite.htm)
 *
 */
#include "cubic_hermite.h"

/// calculate coeffients from the give function values and the derivatives
void eno_cubic_hermite_coeff
  (
    double f[4], ///< [in]  \f$f(0), f(1), f_x(0), f_x(1)\f$
    double c[4]  /**< [out] cubic Hermite coefficients
                   *  0: \f$1\f$, 1: \f$t\f$, 2:\f$t^2\f$, 3:\f$t^3\f$
                   */
  )
{
  c[0] = f[0];
  c[1] = f[2];
  c[2] = 3.0*(-f[0]+f[1])-2.0*f[2]-f[3];
  c[3] = 2.0*( f[0]-f[1])+    f[2]+f[3];
}

double eno_cubic_hermite_interpolate /// interpolate at t using c[]
  (
    double c[4], ///< [in] coefficients obtained by eno_cubic_hermite_coeff()
    double t     ///< [in] desired point \f$0 \le t \le 1\f$
  )
{
  return c[0]+(c[1]+(c[2]+c[3]*t)*t)*t;
}

double eno_cubic_hermite_interpolate_x /// interpolate derivative at t using c[]
  (
    double c[4], ///< [in] coefficients obtained by eno_cubic_hermite_coeff()
    double t     ///< [in] desired point \f$0 \le t \le 1\f$
  )
{
  return c[1]+(2.0*c[2]+3.0*c[3]*t)*t;
} 
