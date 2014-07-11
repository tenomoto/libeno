/// functions for moist process
/*
 * @file: moist.c
 * @author: Takeshi Enomoto
 */
#include "air.h"

/// calculate virtual temperature
double eno_moist_calc_Tv
  (
    double T, /// < [in] temperature, K
    double q  /// < [in] specific humidity, kg/kg
  )
{
  const double eps = eno_air_eps;
  return T*(1.0+(1.0-eps)/eps*q);
}
