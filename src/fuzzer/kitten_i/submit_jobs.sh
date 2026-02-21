#!/bin/bash

# Submit jobs for i from 1 to 50, with issue_based_mutation as true or false

for i in {1..50}; do
  for issue_based_mutation in true false; do
    sbatch run.sh $i $issue_based_mutation
    echo "Submitted job: i=$i, issue_based_mutation=$issue_based_mutation"
  done
done