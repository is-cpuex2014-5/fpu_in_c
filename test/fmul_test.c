#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fpu.h"
#include "minunit.h"

float
fmulAdapter (float x, float y)
{
  union
  {
    float as_float;
    int32_t as_int;
  } a, b, c;
  a.as_float = x;
  b.as_float = y;
  c.as_int = fmul (a.as_int, b.as_int);
  return c.as_float;
}

char *
fmulCornerTest (void)
{
    static char str[1000];
    float a,b,c;
    a = INFINITY, b = rand () / 32;
    c = fmulAdapter (a, b);
    mu_assert ((sprintf(str,"test of fmulCorner not passed!!\nexpected :%f\nreturned :%f\n",a*b,c),str),
	       c == INFINITY);
    a = INFINITY, b = 0;
    c = fmulAdapter (a, b);
    mu_assert ((sprintf(str,"test of fmulCorner not passed!!\nexpected :%f\nreturned :%f\n",a*b,c),str),
	       isnan(c));
    a = 0, b = INFINITY;
    c = fmulAdapter (a, b);
    mu_assert ((sprintf(str,"test of fmulCorner not passed!!\nexpected :%f\nreturned :%f\n",a*b,c),str),
	       isnan(c));
    a = INFINITY, b = NAN;
    c = fmulAdapter (a, b);
    mu_assert ((sprintf(str,"test of fmulCorner not passed!!\nexpected :%f\nreturned :%f\n",a*b,c),str),
	       c == INFINITY);
  return NULL;
}

char *
fmulIntTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = rand () / 32, b = rand () / 32;
      float c = fmulAdapter (a, b);
      mu_assert ((sprintf(str,"test of fmulInt not passed!!\nexpected :%f\nreturned :%f\n",a*b,c),str),
		 fabs (1.0f - a * b / c) <= 0.000001);
    }

  return NULL;
}

char *
fmulTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      float a = frand (), b = frand ();
      // 非正規化数とかはやらない
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL)
	continue;
      float c = fmulAdapter (a, b);
      if (fpclassify (c) != FP_NORMAL || fpclassify (a * b) != FP_NORMAL)
	continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ("test of fmul not passed!!", fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a * b) >= pow (2, 127)
		 || fabs (c - a * b) < max (a * b * pow (2, -22),
					    pow (2, -126)));
    }

  return NULL;
}
