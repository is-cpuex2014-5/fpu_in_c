#!/bin/bash

tests="fmul fadd"

for a in $tests; do
    ./${a}_test > ../${a}.dat
done
