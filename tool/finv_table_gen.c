#include <stdio.h>
#include <stdint.h>
#include "float.h"

extern uint64_t table (uint16_t);

int main (void)
{
    for (int t = 0;t < 1 << 12;t++) {
	print_binary_n(table (t),35);
    }
    
}

