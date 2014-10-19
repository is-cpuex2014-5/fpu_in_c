/*!
  @file fadd.c
  @brief floating addition
 */

#include <stdio.h>
#include "fadd.h"
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
fadd_i (uint32_t a,uint32_t b)
{
  uint32_t mantissa;
  const uint8_t sign = getSign (a);
  uint8_t exp;
  int leading_zero;
  int start_of_round_bit;
  bool carryWhenRound = false;  

  uint32_t u_a = bina(a,30,0),u_b = bina(b,30,0);
  uint8_t e_a = getExp(a),e_b = getExp (b);
  uint32_t m_a = getMant (a),m_b = getMant (b);
  // Stage 1
  {
    dprintf ("e1:%d %d %x %x\n",e_a,e_b,e_a,e_b);
    dprintf ("m1:%d %d %x %x\n",m_a,m_b,m_a,m_b);
    m_a += (1 << 23);
    m_b += (1 << 23);
    dprintf ("m2:%d %d %x %x\n",m_a,m_b,m_a,m_b);
    m_a <<= 3;
    m_b <<= 3;
    dprintf ("m3:%d %d %x %x\n",m_a,m_b,m_a,m_b);
    dprintf ("%d %d %d\n",e_a,e_b,e_a - e_b);
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
    dprintf ("e5:%d %d %x %x\n",e_a,e_b,e_a,e_b);
    dprintf ("m5:%d %d %x %x\n",m_a,m_b,m_a,m_b);

    // Step 5
    leading_zero = ZLC (m_a);
    dprintf ("l_z:%d\n",leading_zero);
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
    dprintf ("e6:%d %d %x %x\n",e_a,e_b,e_a,e_b);
    dprintf ("m6:%d %d %x %x\n",m_a,m_b,m_a,m_b);
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
    
    e_a -= leading_zero - 1;
    if (e_a < (leading_zero - 1) || leading_zero >= 26)
      {
	e_a = 0;
      }    
  }

  // Step 6

  dprintf ("e7:%d %d %x %x\n",e_a,e_b,e_a,e_b);
  dprintf ("m7:%d %d %x %x\n",m_a,m_b,m_a,m_b);  

  exp = bina(e_a,7,0);
  mantissa = bina (m_a,25,3);  
  dprintf ("e,m: %d %d\n",exp,mantissa); 
  
  return makeFloat(sign,exp,mantissa);    
}

uint32_t
fadd (uint32_t a,uint32_t b)
{
  uint32_t u_a = bina(a,30,0),u_b = bina(b,30,0);
  // Step 1
  if ( u_a > u_b ) 
    {
      return fadd_i (a,b);
    }  
  else
    {
      return fadd_i (b,a);
    }
}
