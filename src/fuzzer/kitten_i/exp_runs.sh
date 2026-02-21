#!/bin/bash

for i in {1..50}; do
  for issue_based_mutation in true false; do
    bash run.sh $i $issue_based_mutation &
    echo "Started job: i=$i, issue_based_mutation=$issue_based_mutation"
  done
done

wait
echo "All jobs finished."
