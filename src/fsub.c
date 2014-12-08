/*!
  @file fsub.c
  @brief floating subtruction
 */

#include <stdio.h>
#include "fpu.h"
#include "float.h"

static int
ZLC (uint32_t a)
{
  if (!a) 
    {
      return 28;
    }
  
  if (a >> 27) 
    {
      return 0;
    }
  else
    {      
      return 1 + ZLC (a << 1);
    }  
}

//! abs(a) > abs(b) の前提の元計算する.
static uint32_t
fsub_i (const uint32_t a,const uint32_t b)
{
  uint32_t mantissa;
  const uint8_t sign = getSign (a);
  uint8_t exp;
  int leading_zero;
  bool carryWhenRound = false;  

  uint8_t e_a = getExp(a),e_b = getExp (b);
  uint32_t m_a = getMant (a),m_b = getMant (b);

  // Stage 1
  {
    m_a += (1 << 23);
    m_b += (1 << 23);
    m_a <<= 3;
    m_b <<= 3;
    if (e_a - e_b > 27)
      {      
	m_b = 0;
      }
    else
      {
	m_b >>= (e_a - e_b);
      }  
  }

  //Stage 2
  {
    // Step4
    if (getSign (a) == getSign (b)) 
      {
	m_a += m_b;
      }
    else
      {
	m_a -= m_b;
      }

    // Step 5
    leading_zero = ZLC (m_a);
    carryWhenRound = (bina (m_a,26 - leading_zero,4 - leading_zero) == (1 << 23) - 1);    

    switch (bina (leading_zero,1,0))
      {
      case 0:
	m_a >>= 1;
	break;	
      case 1:
	break;	
      case 2:
	m_a <<= 1;
	break;	
      case 3:
	m_a <<= 2;
	break;	
      }    
  }

  // Stage 3
  {
    if (bina (leading_zero,4,2) == 0)
      {	
	if ( bin(m_a,2) && ( bin (m_a,1) || bin (m_a,3)))
	  {
	    m_a += 8;
	    if (carryWhenRound)
	      {
		m_a >>= 1;
		++e_a;
	      }
	  }
      }    
    else 
      {
	m_a <<= (bina (leading_zero,4,2) << 2);	
      }

    if (e_a < (leading_zero - 1) || leading_zero >= 26)
      {
    	e_a = 0;
      }
    else
      {
	e_a -= leading_zero - 1;
      }    
  }

  // Step 6

  exp = bina(e_a,7,0);
  mantissa = bina (m_a,25,3);  

  if (e_a == 0)
      return changeSign(sign, b);
  if (e_b == 0)
      return changeSign(sign, a);

  return makeFloat(sign,exp,mantissa);    
}

uint32_t
fsub (uint32_t a,uint32_t b)
{
  uint32_t u_a = bina(a,30,0),u_b = bina(b,30,0);
  b += 1 << 31;
  // Step 1
  if ( u_a > u_b ) 
    {
      return fsub_i (a,b);
    }  
  else
    {
      return fsub_i (b,a);
    }
}
