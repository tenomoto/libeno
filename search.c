/// search functions
/*
 * @file: search.c
 * @author: Takeshi Enomoto
 *
 */
#include <stdbool.h>
#include "search.h"

int eno_search_linear /// linear search
  (
    double *y, /// < [in] asending or descending array
    int n,     /// < [in] array length
    double x,  /// < [in] value to match
    int i0     /// < [in] starting value
  )
{
// asecnding  y: s =  1
// descending y: s = -1
  int s = SIGN(y[n-1] - y[0]);
// out of range
  if (s * (x-y[0]) < 0.0) {
    return -1; 
  } else if (s*(x-y[n-1])>=0.0) {
    return n - 1;
  }
  i0 = MAX(0, MIN(n-2, i0));

  int i;
  if (s * (x - y[i0 + 1]) < 0.0) {
    if (s * (x - y[i0]) >= 0.0) {
// ascending y: y[i0] <= x < y[i0+1]
// descending y: y[i0] > x >= y[i0+1]
      i = i0;
    } else {
// search with decreasing i
      for (int j = 0; j < i0 + 1;  j++) {
        i = i0 - j;
        if (s * (x - y[i]) >= 0.0) {
          break;
        }
      }
    }
  } else {
// search with increasing i
    for (i = i0 + 1; i < n-1; i++) {
      if (s * (x - y[i + 1]) < 0.0) {
        break;
      }
    }
  }
  return i;
}

int eno_search_bisection /// bisection search
  (
    double *y, /// < [in] asending or descending array
    int n,     /// < [in] array length
    double x   /// < [in] value to match
  )
{
  int i;
  int il;
  int im;
  int iu;
  bool lascend;

  lascend = y[n-1] > y[0];
  il = -1;
  iu =  n;
  while (iu - il > 1) {
    im = (iu + il) / 2;
    if (EQV(x > y[im], lascend)) {
      il = im;
    } else {
      iu = im;
    }
  }
  return il;
}
