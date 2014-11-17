#include <stdlib.h>
#include "fpu.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>
#include <math.h>

char *
floorTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      uint32_t a = frand ();
      const uint32_t c = h_floor(a);
      if (fabs(i2f (a)) >= pow (2,31) || isnan (i2f(a)))
	  continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of floor not passed!!\nexpected :%e\nreturned :%d\n%d %d %d",
		   i2f(a) , c,c,c+1,c-1), str),c == (int)i2f (a));
    }

  return NULL;

}
