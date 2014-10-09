/*!
  @file float.c
  @brief 浮動小数点の扱いで使う諸々のutility
 */

#include "float.h"

int32_t
f2i (uint32_t a)
{
  union
  {
    float as_float;
    int32_t as_int;
  } ret;  
  ret.as_float = a;

  return ret.as_int;  
}

uint32_t
i2f (int32_t a)
{
  union
  {
    float as_float;
    int32_t as_int;
  } ret;
  ret.as_int = a;

  return ret.as_float;  
}

