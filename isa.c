/// International Standard Atmosphere
/*
 * @file: isa.c
 * @author: Takeshi Enomoto
 */
static const int n = 8;
static const double h[n] = {0.0, 11.0e3, 20.0e3, 32.0e3, 47.0e3, 51.0e3, 71.0e3, 84.852e3}; /// base geopotential height, m
static const double z[n] = {0.0, 11.019e3, 20.063e3, 32.0162e3, 47.350e3, 51.413e3, 71.802e3, 86.0e3}; /// base geometrical height, m
static const double dTdz[n-1] = {-6.5e-3, 0.0, 1.0e-3, 2.8e-3, 0.0e-3, -2.8e-3, -2.0e-3};   /// lapse rate, K/m
static const double T[n] = {15.0, -56.5, -56.5, -44.5, -2.5, -2.5, -58.5, -86.28}; /// base temperature, C
static const double p[n] = {101325.0, 22632.0, 5474.9, 868.02, 110.91, 66.939, 3.9564, 0.3734}; /// base pressure, Pa

double eno_isa_h(int i) {return h[i];}
double eno_isa_z(int i) {return z[i];}
double eno_isa_dTdz(int i) {return dTdz[i];}
double eno_isa_T(int i) {return T[i];}
double eno_isa_p(int i) {return p[i];}
