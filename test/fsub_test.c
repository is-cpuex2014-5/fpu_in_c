#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fsub.h"
#include "minunit.h"

float
fsubAdapter (float x, float y)
{
  union
  {
    float as_float;
    int32_t as_int;
  } a, b, c;
  a.as_float = x;
  b.as_float = y;
  c.as_int = fsub (a.as_int, b.as_int);
  return c.as_float;
}

char *
fsubIntTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = rand () / 32, b = rand () / 32;
      float c = fsubAdapter (a, b);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of fsubInt not passed!!\nexpected :%f\nreturned :%f\n",
		   a - b, c), str), fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a - b) >= pow (2, 127)
		 || fabs (c - (a - b)) <
		 max (max (fabs (a) * pow (2, -23), fabs (b) * pow (2, -23)),
		      max (fabs (a - b) * pow (2, -23), pow (2, -126))));      
    }

  return NULL;
}

char *
fsubTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = frand (), b = frand ();
      // 非正規化数とかはやらない
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL)
	continue;
      float c = fsubAdapter (a, b);
      if (fpclassify (c) != FP_NORMAL || fpclassify (a - b) != FP_NORMAL)
	continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of fsubInt not passed!!\nexpected :%f\nreturned :%f\n",
		   a - b, c), str), fabs (a) >= pow (2, 127)
		 || fabs (b) >= pow (2, 127) || fabs (a - b) >= pow (2, 127)
		 || fabs (c - (a - b)) <
		 max (max (fabs (a) * pow (2, -23), fabs (b) * pow (2, -23)),
		      max (fabs (a - b) * pow (2, -23), pow (2, -126))));      
    }

  return NULL;
}
