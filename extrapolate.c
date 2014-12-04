/// Extrapolation below surface
/*
 * @file: extrapolate.c
 * @author: Takeshi Enomoto
 */
#include <math.h>
#include "extrapolate.h"
double calc_y
  (
    double gamma, /// < [in] Lapse rate
    double sig    /// < [in] full-level p/ps just above the surface
  )
{
  const double rg = eno_air_Rd / eno_earth_gravity;
  return gamma * rg * log(sig);
}

double eno_extrapolate_Ts /// calculate surface temperature
  (
    double Tl,  /// < [in] full-level temperature just above the surface
    double sigl /// < [in] full-level p/ps just above the surface
  )
{
  const double rgg = eno_isa_dTdz(0) * eno_air_Rd / eno_earth_gravity;
  return Tl * (1.0 + rgg*(sigl - 1.0));
}

double eno_extrapolate_z /// extrapolate geopotential height
  (
    double zs, /// < [in] surface geopotential height, m
    double Ts, /// < [in] surface temperature
    double sig /// < [in] full-level p/ps
  )
{
  const double rdg = eno_air_Rd / eno_earth_gravity;
  double gamma = -eno_isa_dTdz(0);
  double y = calc_y(gamma, sig);
  return zs - rdg * Ts * log(sig) * (1.0 + (0.5 + y / 0.6) * y);
}

double eno_extrapolate_T /// extrapolate temperature
  (
    double zs, /// < [in] surface geopotential height, m
    double Ts, /// < [in] surface temperature
    double sig /// < [in] full-level p/ps
  )
{
  double gamma = -eno_isa_dTdz(0);
  if (zs > 2000.0) {
    double T1 = Ts + gamma * zs;
    double T0 = MIN(T1, 298.0);
    if (zs <= 2500.0) {
      T0 = (T0 - T1)/(2500.0 - 2000.0)*(zs - 2000.0) + T1;
    }
    gamma = MAX(T0 - Ts, 0.0)/zs;
  }
  double y = calc_y(gamma, sig);
  return Ts * (1.0 + (1.0 + (0.5 + y/6.0) * y) * y);
}
