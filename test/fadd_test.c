#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fpu.h"
#include "minunit.h"

float
faddAdapter (float x, float y)
{
  union
  {
    float as_float;
    int32_t as_int;
  } a, b, c;
  a.as_float = x;
  b.as_float = y;
  c.as_int = fadd (a.as_int, b.as_int);
  return c.as_float;
}

char *
faddIntTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = rand (), b = rand ();
      float c = faddAdapter (a, b);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of faddInt not passed!!\nexpected :%f\nreturned :%f\n",
		   a + b, c), str), fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a + b) >= pow (2, 127)
		 || fabs (c - (a + b)) <
		 max (max (fabs (a) * pow (2, -23), fabs (b) * pow (2, -23)),
		      max (fabs (a + b) * pow (2, -23), pow (2, -126))));      
    }

  return NULL;
}

char *
faddTest (void)
{
  for (int i = 0; i < 100000; i++)
    {
      static char str[1000];
      float a = frand (), b = frand ();
      // 非正規化数とかはやらない
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL)
	continue;
      float c = faddAdapter (a, b);
      if (fpclassify (a + b) != FP_NORMAL)
	continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of fadd not passed!!\nexpected :%f\nreturned :%f\n",
		   a + b, c), str), fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a + b) >= pow (2, 127)
		 || fabs (c - (a + b)) <
		 max (max (fabs (a) * pow (2, -23), fabs (b) * pow (2, -23)),
		      max (fabs (a + b) * pow (2, -23), pow (2, -126))));      
    }

  return NULL;
}
