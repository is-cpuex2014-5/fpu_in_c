/*!
  @file fmul.h
  @brief floating multiply
*/

#include "fmul.h"
#include "float.h"
#include <stdio.h>

uint32_t
fmul (uint32_t a,uint32_t b)
{
  const uint8_t sign = xor(getSign(a),getSign(b));
  uint16_t exp;
  uint64_t mantissa;  
  uint8_t msb,r = 0;  
  int i;  
  
  if (isInf(a))
    {
      return changeSign(sign,a);
    } 
  else if (isInf(b))
    {
      return changeSign(sign,b);
    }
  else if (isNaN(a))  
    {
      return a;
    }
  else if (isNaN(b))
    {
      return b;
    }
  else if (isZero(a))
    {
      return changeSign(sign,a);
    }
  else if (isZero(b))
    {
      return changeSign(sign,b);
    }
  exp = (uint16_t)(getExp(a) + getExp(b) - 127);
  
  mantissa = ((uint64_t)(1 << 23 | getMant(a)) * (uint64_t)(1 << 23 | getMant(b)));
  for (i = 0; i < 22; ++i)
    {
      r |= mantissa & 1;
      mantissa >>= 1;
    }
  mantissa = (mantissa << 1) | r;    
  msb = (mantissa & (1 << 26)) ? 1 : 0;
  r = mantissa & 2;
  for (i = 0; i < 24; i++)
    {
      r &= mantissa & (1 << i + 2);
    }  
  if (msb || r)  
    {
      ++exp;
    }
  if ((mantissa & 2) && ((mantissa & 1) | (mantissa & 4)) )
    {
      mantissa += 4;
    }
  if (msb || r) 
    {
      mantissa >>= 3;
    }
  else
    {
      mantissa >>= 2;
    }
  
  mantissa &= ((1 << 23) - 1);
  
  return makeFloat(sign,exp,mantissa);  
}
