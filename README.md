# libeno

A collections of C functions that may be useful for analysis and model development
in atmospheric science.
Functions are mainly translated from [enomo](https://github.com/tenomoto/enomo) and
added as I need.

## Requirements

* [Makeheaders](http://www.hwaci.com/sw/mkhdr/): a simple utility to generate .h
* cunit: used for testing

## Available functions by source files

### Computer

* endian.c: Endian transformation

### Constants

* earth.c: Constants of the Earth
* air.c: Atmospheric constants

### Mathematical functions

* emath.c: Math functions missing in C
* xreal.c: Extended exponent of floating-point numbers
* sphere.c: Functions related to a sphere
* alf.c: Functions to Calculate normalized associated Legendre functions

### Search and interpolation

* search.c: search functions
* cubic_lagrange.c: Cubic Lagrange interpolation
* cubic_hermite.c: Cubic Hermite interpolation
* bicubic.c: Bicubic interpolation
* biquadratic.c:  Biquadratic interpolation

### Meteorology

* isa.c: International Standard Atmosphere
* moist.c: functions for moist process
* extrapolate.c: Extrapolation below surface
* sigmap.c: Hybrid sigma-p coordinates
