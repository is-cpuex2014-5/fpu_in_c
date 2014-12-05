#include <stdlib.h>
#include "fpu.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

char *
i2fTest (void)
{
  for (int32_t i = INT32_MIN; i < INT32_MAX; i++)
    {
      union {
	int32_t s;
	uint32_t u;
      } a;
      a.s = i;
      static char str[1000];
      uint32_t c = h_i2f(a.u);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of i2f not passed!!\nexpected :%d\nreturned :%g\n%g %g %g",
		   a.s , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),
		 (isnan (i2f (c+1)) || fabs(i2f (c) - a.s) <= fabs(i2f (c+1) - a.s)) && 
		 (isnan (i2f (c-1)) || fabs(i2f (c) - a.s) <= fabs(i2f (c-1) - a.s)));
    }

  return NULL;

}
