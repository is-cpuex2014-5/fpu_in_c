#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "float.h"
#include "minunit.h"
#include "fpu.h"

char *
fabsTest (void)
{
  for (uint32_t i = 0; i < UINT32_MAX; i++)
    {
      static char str[1000];
      const uint32_t a = i;
      const uint32_t c = h_fabs (a);

      mu_assert ((sprintf
      		  (str,
      		   "test of fabs not passed!!\ncase %d\nexpected :%d\nreturned :%d\n",
      		   i,f2i(fabs(i2f(a))),c),str),f2i(fabs(i2f(a))) == c);
		 
    }

  return NULL;
}
