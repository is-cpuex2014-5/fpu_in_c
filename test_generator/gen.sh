#!/bin/bash

tests="fmul fadd fsub floor i2f finv"

for a in $tests; do
    ./${a}_test > ../${a}.dat
done
