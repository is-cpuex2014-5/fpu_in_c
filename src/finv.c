#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "float.h"

#define M (1.0/2048)


struct a_b
{
  uint16_t a;
  uint32_t b;
};
  

//! key (12bit) -> a (12bit) & b (23bit)
uint64_t
table (uint16_t key)
{
  union uint32_f
  {
    float as_float;
    uint32_t as_int;
  };
  double t = 1 + (M * (key >> 1));  

  union uint32_f a;a.as_float = (double) -1 / (t * (t+M));
  const uint32_t h_a = getMant (a.as_int) >> 11 | 1 << 12;
  const uint32_t h_b = key | 1 << 12;
  const uint32_t l_a = getMant (a.as_int) & ((1 << 11) - 1);
  const uint32_t HH = h_a * h_b;
  const uint32_t LH = l_a * h_b;
  uint32_t mul = 1 + (((HH >> 1) + (LH >> 12)) >> 0) ;
  bool f = (mul & 1 << 24);
  mul >>= (f ? 1 : 0);

  union uint32_f tmp;tmp.as_float = sqrt (1/t) + sqrt (1/(t+M));

  union uint32_f b;b.as_float = (tmp.as_float * tmp.as_float)/2;
  uint32_t ret_a = (getMant(a.as_int) >> 11 | 1 << 12) >> (f ? 2 : 1);
  uint32_t ret_b = getMant(b.as_int) - (getMant(mul) >> 1);

  return (uint64_t) ret_a << 23 | ret_b;
}



uint32_t
finv (uint32_t in)
{
  const uint8_t sign = getSign (in);
  const uint16_t key = getMant (in) >> 11;
  const uint8_t expr = 126 + 127 - getExp (in);
  if (getMant (in) == 0) 
    {
      return makeFloat (sign,expr+1,0);
    }

  const uint64_t raw_ret = table(key);
  printf ("key %d\n",key);
  printf ("raw_ret %lx\n",raw_ret);
  const uint32_t a = raw_ret >> 23;
  const uint32_t b = bina(raw_ret,22,0);
  const uint32_t l_b = getMant (in) & ((1 << 11) - 1);
  const uint32_t HL = a * l_b;

  const uint32_t mulb = (HL >> 12);
  const uint32_t mantissa = (b - mulb);
  return makeFloat (sign,expr,getMant(mantissa << 1));  
}
