#include <stdbool.h>
#include <math.h>
#include "emath.h"

double fmod(double x, double y)
{
  return FMOD(x,y);
}

double max(double x, double y)
{
  return MAX(x,y);
}

double min(double x, double y)
{
  return MIN(x,y);
}

double sign(double x)
{
  return SIGN(x);
}

bool eqv(bool x, bool y)
{
  return EQV(x,y);
}

bool xor(bool x, bool y)
{
  return XOR(x,y);
}

double ipow(double x, int n)
{
  double y = 1.0;

  if (n < 0) {
    x = 1.0 / x;
    n = -n;
  }
  
  do {
    if (n & 1) { // executed in the first loop if n is odd and
      y *= x;    // in the last loop
    }
    n >>= 1;   // n /= 2
    x *= x; 
  } while (n); // n > 0
  return y;
}
