/// Atmospheric constants
/*
 * @file: air.c
 * @author: Takeshi Enomoto
 */
const double eno_air_Rd =  287.0;   /// gas constant of dry air, J/deg/kg
const double eno_air_cp = 1004.0;   /// specific heat at constant pressure, J/deg/kg
const double eno_air_cv =  717.0;   /// specific heat at constant volume, J/deg/kig
const double eno_air_p0 = 1013.0e2; /// reference pressure, Pa
const double eno_air_T0 =  273.15;  /// freezing temperature, K
const double eno_air_Rv =  461.0;   /// gas constat of water vapour, J/deg/kg
const double eno_air_kappa = eno_air_Rd/eno_air_cp; /// kappa = Rd/cp
const double eno_air_gamma = eno_air_cp/eno_air_cv; /// gamma = cp/cv
const double eno_air_eps = eno_air_Rd/eno_air_Rv;   /// eps = Rd/Rv
