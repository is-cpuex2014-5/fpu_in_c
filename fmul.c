/*!
  @file fmul.h
  @brief floating multiply
*/

#include "fmul.h"
#include "float.h"
#include <stdio.h>

static int flag = 0;

static uint32_t
calcMantissa (uint32_t a,uint32_t b)
{
  uint32_t h_a = a >> 11,h_b = b >> 11,l_a = a & ((1 << 11) - 1),l_b = b & ((1 << 11) - 1),c;
  int ptr = 32;
  
  h_a |= 1 << 12;
  h_b |= 1 << 12;
  c = h_a * h_b + ((h_a * l_b) >> 11) + ((l_a * h_b) >> 11) + 2;

  flag = 0;  
  while (ptr > 23) 
    {
      if (c & (1 << ptr)) 
	{
	  ++flag;
	  c >>= 1;
	}      
      ptr--;      
    }  
  
  return c & ((1 << 23) - 1);
}

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
      if (isZero(b))
	{
	  return m_Nan;	  
	}      
      return changeSign(sign,a);
    } 
  else if (isInf(b))
    {
      if (isZero(a))
	{
	  return m_Nan;	  
	}      
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
  exp = (getExp(a) + getExp(b) + 129);
  
  if (!(exp & (1 << 8)) || exp == 0) 
    exp = 0;  
  
  mantissa = calcMantissa (getMant(a),getMant(b));
  if (flag > 1) 
    {
      exp ++;
    }
  
  mantissa &= ((1 << 23) - 1);
  exp &= ((1 << 8) - 1);
  return makeFloat(sign,exp,mantissa);  
}
