#include <stdlib.h>
#include "float.h"
#include "minunit.h"
#include <stdio.h>
#include <math.h>

uint32_t
fsqrt (uint32_t);

char *
fsqrtTest (void)
{
  for (uint32_t i = 0; i < UINT32_MAX; i++)
    {
      static char str[1000];
      uint32_t a = i;
      uint32_t c = fsqrt(a);
#define max(A,B) ((A) > (B) ? (A) : (B))
      // 非正規化数は除く;
      if (getExp (a) == 0)
	{
	  continue;
	}
      if (isnan (i2f(a)))
	{
	  continue;
	}
      mu_assert("special case does not passed!!\n", a != 0x3F800001 || c == 0x3F800000);

      mu_assert ((sprintf
      		  (str,
      		   "test of fsqrt not passed!!\ncase %d\nexpected :%d\nreturned :%d\nexpected :%x %x\nreturned :%x %x\n",
      		   i,f2i(sqrt(i2f(a))) , c,getExp(f2i(sqrt(i2f(a)))),getMant(f2i(sqrt(i2f(a)))),getExp (c),getMant (c)),str),
		 i2f(a) < 0 ||  i2f(a) >= pow (2,127) || fabs(i2f(c) - sqrt(i2f(a))) <= max (pow (2,-126),sqrt (i2f(a)) * pow (2,-20)));
    }

  return NULL;

}
