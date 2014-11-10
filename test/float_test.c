#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "minunit.h"
#include "float.h"

static int
getSignTestUnit (float test)
{    
  uint32_t *a;
  a = (uint32_t *) & test;
  
  int ret = (test < 0) == getSign (*a) || test == 0 || isnan (test);

  return ret;
}

char *
getSignTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
      mu_assert("test of getSign not passed!!",getSignTestUnit (frand ()));
    }

  return NULL;
}


static int
makeFloatTestUnit (float test)
{
  uint32_t *a;
  a = (uint32_t *) & test;

  return *a = makeFloat (getSign (*a), getExp (*a), getMant (*a));
}

char *
makeFloatTest (void)
{
  for (int i = 0; i < 1000; i++)
    {
	mu_assert ("test of makeFloat not passed!!",makeFloatTestUnit (frand ()));
    }

  return NULL;
}

char *
constTest (void)
{
  union
  {
    float as_float;
    int32_t as_int;
  } i, n;
  i.as_int = m_Inf;
  n.as_int = m_Nan;
  mu_assert ("test of m_Nan not passed!!",isnan (n.as_float));

  mu_assert ("test of m_Inf not passed!!",isinf (i.as_float));

  return NULL;
}
