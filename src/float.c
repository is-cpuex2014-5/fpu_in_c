/*!
  @file float.c
  @brief 浮動小数点の扱いで使う諸々のutility
 */

#include <stdio.h>
#include "float.h"

int32_t
f2i (float a)
{
  union
  {
    float as_float;
    int32_t as_int;
  } ret;  
  ret.as_float = a;

  return ret.as_int;  
}

float
i2f (uint32_t a)
{
  union
  {
    float as_float;
    uint32_t as_int;
  } ret;
  ret.as_int = a;

  return ret.as_float;  
}

void
print_binary (const uint32_t a)
{
  for (int t = 31; t >= 0;t--) 
    {
      putchar (a & (1 << t) ? '1' : '0');      
    }
  putchar ('\n');  
}

void
fprint_binary (FILE* stream,const uint32_t a)
{
  for (int t = 31; t >= 0;t--) 
    {
      putc (a & (1 << t) ? '1' : '0',stream);
    }
}

void
print_binary_n (const uint64_t a,int b)
{
  for (int t = b - 1; t >= 0;t--) 
    {
      putchar ((a >> t) & 1 ? '1' : '0');      
    }
  putchar ('\n');  
}
