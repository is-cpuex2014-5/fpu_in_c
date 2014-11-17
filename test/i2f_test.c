#include <stdlib.h>
#include "fpu.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>

char *
i2fTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      uint32_t a = rand () | rand () << 15;
      uint32_t c = h_i2f(a);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of i2f not passed!!\nexpected :%d\nreturned :%e\n%e %e %e",
		   a , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),a != 0 &&  abs(i2f (c) - a) <= abs(i2f (c+1) - a) && abs(i2f (c) - a) <= abs(i2f (c-1) - a));
    }

  return NULL;

}
