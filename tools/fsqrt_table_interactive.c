#include <stdio.h>
#include <stdint.h>
#include "float.h"

extern uint64_t
fsqrt_table (uint16_t);

int
main (void)
{
  uint16_t a;
  uint64_t r;  
  scanf ("%hd",&a);
  r = fsqrt_table (a);
  
  printf ("table %lx\n",r);
  print_binary_n (r,46);
  putchar ('\n');
  printf ("a %ld\n",r >> 23);
  printf ("b %ld\n",bina(r,22,0));
  const uint32_t aa = r >> 23;
  const uint32_t b = bina(r,22,0);

  printf ("%x %x\n",aa,b);


  return 0;
}
