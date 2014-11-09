#!/bin/sh

make > /dev/null && ./finv_table_gen | awk '{
    printf "      when %4d => r := \"%s\";\n",NR-1,$0;
}'
