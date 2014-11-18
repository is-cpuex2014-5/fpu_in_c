#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;     \
                                if (message) return message; } while (0)
char str[1000];
extern uint32_t h_i2f (uint32_t a);

union uint32_f
{
  uint32_t i;
  float f;
};

char *
all_tests (void)
{
  puts ("run 20ms");
  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));
  union uint32_f a, c;
  for (uint32_t i = 0; i < UINT32_MAX/100 ; i++)
    {
      fprintf (stderr,"%d\n",i);
      char aa[33],cc[33];
      a.i = i;
      if (i == 0)
	a.i = 0xf0000000;
      if (fpclassify (a.f) != FP_NORMAL)
	  continue;
      c.i = h_i2f (a.i);
      if (fpclassify (c.f) != FP_NORMAL)
      	continue;
      for (int t = 0; t < 32;++t)
	{
	  aa[31 - t] = a.i & (1 << t) ? '1' : '0';
	  cc[31 - t] = c.i & (1 << t) ? '1' : '0';
	}
      aa[32] = '\0';
      cc[32] = '\0';
      // 非正規化数とかはやらない
      if (isnormal (a.f))
	{
	  if (!isnan (c.f))
	    printf ("%s\t%s\n",aa,cc);
	}
    }
  return NULL;
}

int
main (void)
{
  char *result = all_tests ();

  return result != 0;
}
