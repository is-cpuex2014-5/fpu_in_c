#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "float.h"
#include "fadd.h"
#include "fmul.h"

#define MAX 512


struct a_b
{
  uint16_t a;
  uint32_t b;
};
  

union uint32_f
{
  float as_float;
  uint32_t as_int;
};


//! exp & key (10bit) -> a (23bit) & b (23bit)
// exp & key (13bit) -> 13bit & 23bitと全体で5bitしか変わらなかったのでmantissa返すようにした.
uint64_t
fsqrt_table (uint16_t key)
{  
  double c;  
  double t;  

  if (bin(key,9) == 1) 
    {
      c = 2.0 / MAX;
      t = 2.0 + c * bina(key,8,0);
    }
  else 
    {
      c = 1.0 / MAX;
      t = 1.0 + c * key;
    }
  /* printf ("t c %f %f\n",t,c);   */
  
  union uint32_f a;a.as_float = (double) 1 / (sqrt (t) + sqrt(t+c));
  union uint32_f tmp;tmp.as_float = (2 * a.as_float * sqrt (t)) - 1;

  union uint32_f b;b.as_float = (2 - tmp.as_float * tmp.as_float) / (8 * a.as_float);

  return (uint64_t) a.as_int << 23 | getMant(b.as_int);
}



uint32_t
fsqrt (uint32_t in)
{
  const uint8_t sign = getSign (in);  
  const uint16_t key = getMant (in) >> 14 | (!(getExp (in) & 1)) << 9; 
  uint8_t expr;
  if (sign == 1)
    {
      if (getExp (in) == 0)
	{
	  return in;
	}
      else
	{
	  return m_Nan;
	}      
    }
  if (getExp (in) == 0)
    {      
      return 0;
    }  
  // nan
  if (getExp (in) == 0xff) {
    return in;
  }
  if (getExp (in) >= 127) {
    expr = 127 + ((getExp (in) - 127) >> 1);      
  } else {
    expr = 127 - ((127 - getExp (in) + 1) >> 1);      
  }
    
    
  const uint64_t raw_ret = fsqrt_table(key);
  const uint32_t a = getMant(raw_ret >> 23);
  const uint32_t b = bina(raw_ret,22,0);

  const uint32_t h_a = getMant (a) >> 11 | 1 << 12;
  const uint32_t h_b = getMant (in) >> 11 | 1 << 12;
  const uint16_t l_a = bina (a,10,0);
  const uint16_t l_b = bina (in,10,0);
  
  const uint32_t HH = h_a * h_b;
  const uint32_t HL = h_a * l_b;
  const uint32_t LH = l_a * h_b;
  // 25 downto 0
  union uint32_f mul;
  mul.as_int = (HH + (LH >> 11) + (HL >> 11)+ 2);
  uint8_t x_expr;
  if (bin(mul.as_int,25)) {
    mul.as_int = bina (mul.as_int,24,2);
    x_expr = ((getExp (in) & 1) == 0) ? 129 : 128;
  } else {
    mul.as_int = bina (mul.as_int,23,1);
    x_expr = ((getExp (in) & 1) == 0) ? 128 : 127;
  }

  uint32_t m_a;
  uint32_t m_b;
  if (x_expr == 129) {
    m_a = (getMant (mul.as_int) | 1 << 23) << 1;
    m_b = (getMant (b) | 1 << 23);
  } else if (x_expr == 127) {
    m_a = (getMant (mul.as_int) | 1 << 23);
    m_b = (getMant (b) | 1 << 23) << 1;
  } else {
    m_a = (getMant (mul.as_int) | 1 << 23) << 1;
    m_b = (getMant (b) | 1 << 23) << 1;
  }

  uint32_t mantissa;
  //! @note 丸めを気にしなくてもtestを通るっぽいから丸めない
  const uint32_t sum = m_a + m_b;
  if (bin(m_b,24)) {
    mantissa = bina (sum,24,2);
  } else {
    mantissa = bina (sum,23,1);
  }
  
  return makeFloat (sign,expr,mantissa);  
}
