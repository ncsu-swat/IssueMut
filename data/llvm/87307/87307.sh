#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <file> <seed>"
    exit 1
fi

# Delete #pragma omp taskwait 
sed -i "s/#pragma omp taskwait//" "$1"