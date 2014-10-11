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
  
  uint32_t HH,HL,LH;
  uint16_t exp0,exp1,exp;
  uint32_t mantissa;  
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

  // Stage 1
  {
    uint32_t m_a = getMant(a) , m_b = getMant(b);
    // sign
    exp0 = (getExp(a) + getExp(b) + 129);
    if (!(exp0 & (1 << 8)) || exp0 == 0) 
      exp0 = 0;  
    uint32_t h_a = m_a >> 11,h_b = m_b >> 11,l_a = m_a & ((1 << 11) - 1),l_b = m_b & ((1 << 11) - 1);
  
    h_a |= 1 << 12;
    h_b |= 1 << 12;
    HH = h_a * h_b;
    HL = h_a * l_b;
    LH = l_a * h_b;
  }
  
  // Stage 2
  {
    mantissa = HH + ( HL >> 11) + (LH >> 11) + 2;    
    exp1 = exp0 + 1;
  }
  
  // Stage 3
  {
   int flag = 0;
   int ptr = 32;
    while (ptr > 23) 
      {
	if (mantissa & (1 << ptr)) 
	  {
	    ++flag;
	    mantissa >>= 1;
	  }      
	ptr--;      
      }  
    if (flag > 1)
      exp = exp1;
    else
      exp = exp0;
  }
  
  mantissa &= ((1 << 23) - 1);
  exp &= ((1 << 8) - 1);
  return makeFloat(sign,exp,mantissa);  
}
