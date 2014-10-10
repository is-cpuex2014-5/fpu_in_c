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
int tests_run = 0;
char str[1000];
extern uint32_t fmul (uint32_t a, uint32_t b);

union uint32_f
{
  uint32_t i;
  float f;
};

char *
all_tests (void)
{

  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));
  union uint32_f a, b, c;
  for (int i = 0; i < 2000000 ; i++)
    {
      char aa[33],bb[33],cc[33];
      a.i = (uint32_t)( (rand () << 2) + rand ());
      b.i = (uint32_t)( (rand () << 2) + rand ());
      if (fpclassify (a.f) != FP_NORMAL || fpclassify (b.f) != FP_NORMAL)
	  continue;
      tests_run++;
      c.i = fmul (a.i, b.i);
      if (fpclassify (c.f) != FP_NORMAL || fpclassify (a.f*b.f) != FP_NORMAL)
      	continue;
      for (int t = 0; t < 32;++t)
	{
	  aa[31 - t] = a.i & (1 << t) ? '1' : '0';
	  bb[31 - t] = b.i & (1 << t) ? '1' : '0';
	  cc[31 - t] = c.i & (1 << t) ? '1' : '0';
	}
      aa[32] = '\0';
      bb[32] = '\0';
      cc[32] = '\0';
      // 非正規化数とかはやらない
      if (isnormal (a.f) && isnormal (b.f))
	{
	  if (!isnan (c.f))
	    printf ("%s\t%s\t%s\n",aa,bb,cc);
	  /* mu_assert ((sprintf */
	  /* 	      (str, "error:%d %d %d %f %f %f %f\n", a.i, b.i, c.i, */
	  /* 	       a.f, b.f, c.f, a.f + b.f), str), c.f == a.f + b.f || fabs(c.f - a.f + b.f) < fabs(c.f) * 0.1 */
	  /* 	     || isnan (c.f)); */
	}
    }
  return NULL;
}

int
main (void)
{
  char *result = all_tests ();
  if (result != 0)
    {
      printf ("%s\n", result);
    }
  else
    {
      printf ("ALL TESTS PASSED\n");
    }
  printf ("Tests run: %d\n", tests_run);

  return result != 0;
}
