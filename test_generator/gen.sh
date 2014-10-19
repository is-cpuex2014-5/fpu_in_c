#!/bin/bash

tests="fmul fadd fsub"

for a in $tests; do
    ./${a}_test > ../${a}.dat
done
