#!/bin/sh

make > /dev/null && ./fsqrt_table_gen | awk '{
    printf "      when %4d => r := \"%s\";\n",NR-1,$0;
}'
