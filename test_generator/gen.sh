#!/bin/bash

tests="fmul"

for a in $tests; do
    ./${a}_test > ../${a}.dat
done
