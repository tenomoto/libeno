/// Cubic Lagrange interpolation
/**
 * @file cubic_lagrange.c
 * @author Takeshi Enomoto
 *
 *
 * # Algorithm
 *
 * \f[
 * p(x) = \sum_{i=0}^3 l_i(x)y_i
 * \f]
 * where
 * \f[
 * l_i(x) = \prod_{m=0,m\neq i}^3\frac{x-x_m}{x_i-x_0}
 * \f]
 *
 * # Reference
 *
 * - [Lagrange polynomial](http://en.wikipedia.org/wiki/Lagrange_polynomial)
 */
#include "cubic_hermite.h"

double eno_cubic_lagrange
  (
    double xa[4], ///< [in] x_i
    double ya[4], ///< [in] f(x_i)
    double x      ///< [in] x
  )
{
  double y01;
  double y12;
  double y23;
  double y012;
  double y123;

/*
 *  enomo
 *  y12  = ((x-xa(2))*ya(1)+(xa(1)-x)*ya(2))/(xa(1)-xa(2))
 *  y23  = ((x-xa(3))*ya(2)+(xa(2)-x)*ya(3))/(xa(2)-xa(3))
 *  y34  = ((x-xa(4))*ya(3)+(xa(3)-x)*ya(4))/(xa(3)-xa(4))
 */

  y01 = ((x - xa[1]) * ya[0] + (xa[0] - x) * ya[1]) / (xa[0]-xa[1]);
  y12 = ((x - xa[2]) * ya[1] + (xa[1] - x) * ya[2]) / (xa[1]-xa[2]);
  y23 = ((x - xa[3]) * ya[2] + (xa[2] - x) * ya[3]) / (xa[2]-xa[3]);

/*
 *  enomo
 *  y123 = ((x-xa(3))*y12+(xa(1)-x)*y23)/(xa(1)-xa(3))
 *  y234 = ((x-xa(4))*y23+(xa(2)-x)*y34)/(xa(2)-xa(4))
 */

  y012 = ((x - xa[2]) * y01 + (xa[0] - x) * y12) / (xa[0] - xa[2]);
  y123 = ((x - xa[3]) * y12 + (xa[1] - x) * y23) / (xa[1] - xa[3]);

//    y    = ((x-xa(4))*y123+(xa(1)-x)*y234)/(xa(1)-xa(4))

  return ((x - xa[3]) * y012 + (xa[0] - x) * y123) / (xa[0] - xa[3]);
}
