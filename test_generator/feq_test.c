#include <fenv.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "float.h"
#include "fpu.h"

union uint32_f
{
  uint32_t i;
  float f;
};

void
gen_test (void)
{
  union uint32_f a, b;
  bool c;
  for (int i = 0; i < 2000000 ; i++)
    {
      char aa[33],bb[33],cc[2];
      a.i = rand () | rand () << 16;
      b.i = rand () | rand () << 16;
      if (fpclassify (a.f) != FP_NORMAL || fpclassify (b.f) != FP_NORMAL)
	  continue;
      c = feq (a.i,b.i);

      for (int t = 0; t < 32;++t)
	{
	  aa[31 - t] = a.i & (1 << t) ? '1' : '0';
	  bb[31 - t] = b.i & (1 << t) ? '1' : '0';
	}
      aa[32] = '\0';
      bb[32] = '\0';
      cc[0]  = c;
      cc[1]  = '\0';
      // 非正規化数とかはやらない
      if (isnormal (a.f) && isnormal((b.f)))
	{
	  printf ("%s\t%s\t%s\n",aa,bb,cc);
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
