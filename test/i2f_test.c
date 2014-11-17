#include <stdlib.h>
#include "fpu.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>
#include <stdint.h>

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
		   a , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),abs(i2f (c) - a) <= abs(i2f (c+1) - a) && abs(i2f (c) - a) <= abs(i2f (c-1) - a));
    }

  return NULL;

}

char *
i2fWholeTest (void)
{
  for (int i = INT32_MIN; i <= INT32_MAX; i++)
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
		   "test of i2f not passed!!\nexpected :%d\nreturned :%e\n%e %e %e",
		   a.s , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),abs(i2f (c) - a.s) <= abs(i2f (c+1) - a.s) && abs(i2f (c) - a.s) <= abs(i2f (c-1) - a.s));
    }

  return NULL;

}
