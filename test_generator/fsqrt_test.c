#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

extern uint32_t
fsqrt (uint32_t a);

union uint32_f
{
  uint32_t i;
  float f;
};

void
gen_test (void)
{
  union uint32_f a, c;
  for (int i = 0; i < 2000000 ; i++)
    {
      char aa[33],cc[33];
      a.i = rand () | rand () << 16;
      if (fpclassify (a.f) != FP_NORMAL)
	  continue;
      c.i = fsqrt (a.i);
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
}

int
main (void)
{
  fesetround (FE_TOWARDZERO);
  srand((unsigned)time(NULL));

  gen_test ();

  return 0;
}
