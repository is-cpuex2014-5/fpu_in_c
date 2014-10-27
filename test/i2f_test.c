#include <stdlib.h>
#include "i2f.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>

char *
i2fTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      uint32_t a = rand () / 32;
      uint32_t c = h_i2f(a);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of i2f not passed!!\nexpected :%d\nreturned :%d\n%d %d %d",
		   a , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),a != 0 &&  abs(i2f (c) - a) <= abs(i2f (c+1) - a) && abs(i2f (c) - a) <= abs(i2f (c-1) - a));
    }

  return NULL;

}
