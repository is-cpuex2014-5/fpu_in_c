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
extern uint32_t fadd (uint32_t a, uint32_t b);

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
      c.i = fadd (a.i, b.i);
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
