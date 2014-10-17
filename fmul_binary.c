#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

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
      scanf ("%32s\t%32s",aa,bb);
      tests_run++;
      a.i = 0;
      b.i = 0;
      for (int t = 0; t < 32;++t)
	{
	  a.i += (aa[t] - '0') << t;
	  b.i += (bb[t] - '0') << t;
	}
      c.i = fmul (a.i, b.i);      
      for (int t = 0; t < 32;++t)
	{
	  aa[31 - t] = a.i & (1 << t) ? '1' : '0';
	  bb[31 - t] = b.i & (1 << t) ? '1' : '0';
	  cc[31 - t] = c.i & (1 << t) ? '1' : '0';
	}
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

  if (result != 0)
    {
      fprintf (stderr,"%s\n", result);
    }
  else
    {
      fprintf (stderr,"ALL TESTS PASSED\n");
    }
  fprintf (stderr,"Tests run: %d\n", tests_run);

  return result != 0;
}
