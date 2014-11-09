#include <stdlib.h>
#include "fpu.h"
#include "float.h"
#include "minunit.h"
#include <stdio.h>

char *
floorTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      static char str[1000];
      uint32_t a = rand () / 32;
      uint32_t c = h_floor(a);
#define max(A,B) ((A) > (B) ? (A) : (B))
      mu_assert ((sprintf
		  (str,
		   "test of floor not passed!!\nexpected :%d\nreturned :%d\n%d %d %d",
		   a , i2f(c),i2f (c),i2f (c+1),i2f (c-1)), str),a != 0 &&  abs(a) >= abs(i2f (c)) && abs(i2f (c)) <= abs(a) +1);
    }

  return NULL;

}
