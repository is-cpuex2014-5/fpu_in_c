#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float.h"
#include "minunit.h"
#include "fpu.h"

bool
fltAdapter (float a,float b)
{
  return flt (f2i (a),f2i (b));  
}


char *
fltTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      float a = frand (), b = frand ();

      // 非正規化数とかはやらない
      if (fpclassify (a) != FP_NORMAL || fpclassify (b) != FP_NORMAL)
	continue;
      bool c = fltAdapter (a, b);
      mu_assert ((sprintf
		  (str,
		   "test of flt not passed!!\nexpected :%d\nreturned :%d\n",
		   a < b, c), str), (a < b) == c);      
    }

  return NULL;
}
