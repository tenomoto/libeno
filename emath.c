#include <math.h>
double  eno_emath_mod(double x, double y) {
  return x - y*floor(x/y);
}
