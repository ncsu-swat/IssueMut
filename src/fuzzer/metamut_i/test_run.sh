#!/bin/bash

working_dir=$(pwd)

mkdir workspace

cd workspace

python3 ../fuzzer/run.py -j 10 --wdir $working_dir/workspace --repeat-times 5 --duration 300 --seeds-dir $working_dir/seeds/ --seed 0

