#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minunit.h"
#include "fpu.h"

float
fdivAdapter (float x, float y)
{
  union
  {
    float as_float;
    int32_t as_int;
  } a, b, c;
  a.as_float = x;
  b.as_float = y;
  c.as_int = fdiv(a.as_int, b.as_int);
  return c.as_float;
}

char *
fdivTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = frand (), b = frand ();
      // 非正規化数とかはやらない
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL )
	continue;
      float c = fdivAdapter (a, b);
      if (fpclassify (c) != FP_NORMAL || fpclassify (a / b) != FP_NORMAL)
	continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of fdiv not passed!!\nexpected :%e\nreturned :%e\n",
		   a / b, c), str), fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a / b) >= pow (2, 127)
		 || fabs (c - (a / b)) <
		 max (fabs (a/b) * pow (2,-20), pow (2, -126)));      
    }

  return NULL;
}
