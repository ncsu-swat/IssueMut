#!/bin/bash

number_of_agents=15
number_of_jobs=$((2 * number_of_agents))

# seconds
time=86400

working_dir=$(pwd)

method="metamut_i"

seeds=(2034567890 157839206 4037289401 1324675832 2947583017 1908234765 3284957103 2763891275 3746283957 1092387456)

# Loop from 0 to 4
for i in {0..4}; do
    dir="$method-$i"
    
    # Create the directory if it doesn't exist
    mkdir -p "$dir"

    # Navigate into the directory
    cd "$dir" || exit

    echo ${seeds[$i]}

    # Run the Python script
    python3 ../fuzzer/run.py -j ${number_of_jobs} \
      --wdir $working_dir/$dir \
      --repeat-times ${number_of_agents} \
      --duration ${time} \
      --seeds-dir $working_dir/seeds \
      --cc-opt=-O2 \
      --seed ${seeds[$i]}

    # Return to the original directory
    cd ..
done
