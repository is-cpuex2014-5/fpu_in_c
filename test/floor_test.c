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
      union {
	int32_t s;
	uint32_t u;
      } a,c;
      a.s = frand ();
      c.u = h_floor(a.u);
      if (fabs(i2f (a.u)) >= pow (2,31) || isnan (i2f(a.u)))
	  continue;
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of floor not passed!!\nexpected :%e\nreturned :%d\n%d %d %d",
		   i2f(a.u) , c.u,c.u,c.u+1,c.u-1), str),c.s == (int)i2f (a.u));
    }

  return NULL;

}

char *
floorWholeTest (void)
{
  for (uint32_t i = 0; i < UINT32_MAX; i++)
    {
      static char str[1000];
      union {
	int32_t s;
	uint32_t u;
      } a,c;
      a.u = i;
      c.u = h_floor(a.u);
      /* if (fabs(i2f (a.u)) >= pow (2,31) || isnan (i2f(a.u))) */
      /* 	  continue; */
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of floorWhole not passed!!\nexpected :%d\nreturned :%d\n%g %g %g",
		   (int) i2f(a.u) , c.u,i2f(a.u),i2f(a.u+1),i2f(a.u-1)), str),c.s == (int)i2f (a.u));
    }
  return NULL;

}
