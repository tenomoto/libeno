/// constants of the Earth
/*
 * @file: earth.c
 * @author: Takeshi Enomoto
 */
#include <math.h>
#include "earth.h"
const double eno_earth_radius =  6.371e6;               /// radius
const double eno_earth_daysec = 86400.0;                /// 24 h in seconds
const double eno_earth_omega = 2*M_PI/eno_earth_daysec; /// angular velocty
const double eno_earth_gravity = 9.80665;               /// gravity
