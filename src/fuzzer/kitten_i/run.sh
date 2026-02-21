#!/bin/bash
export TMPDIR="/root/perses/kitten/experiment/kitten/temp"
mkdir -p $TMPDIR

i=$1 # run number and seed number
issue_based_mutation=$2
CAMPAIGN_ROOT_DIR="kitten/$issue_based_mutation-issue-8h-$i"

FINDING_FOLDER="${CAMPAIGN_ROOT_DIR}/default_finding_folder"
MUTANTS_FOLDER="${CAMPAIGN_ROOT_DIR}/default_mutants_folder"
LOG_FILE="${CAMPAIGN_ROOT_DIR}/testing-process.log"

mkdir -p "${CAMPAIGN_ROOT_DIR}"
mkdir -p "${FINDING_FOLDER}"
mkdir -p "${MUTANTS_FOLDER}"

java -Xmx7G -Xms2G -jar ../kitten_deploy.jar --testing-config config.yaml \
  --random-seed $i \
  --timeout 28800 \
  --threads 1 \
  --max-recursions 5 \
  --enable-splicing true \
  --enable-issue-based-mutator $issue_based_mutation \
  --generator "RANDOM_GENERATOR" \
  --enable-deleting-on-random-positions true \
  --enable-deleting-on-continuous-positions true \
  --enable-inserting-on-random-positions true \
  --enable-inserting-on-continuous-positions true \
  --enable-replacing-on-random-positions true \
  --enable-replacing-on-continuous-positions true \
  --enable-replacing-identifier true \
  --enable-replacing-same-type-token true \
  --fuzzer-mode NORMAL_FUZZING \
  --verbosity "INFO" \
  --mutants-folder ${MUTANTS_FOLDER} \
  --finding-folder ${FINDING_FOLDER} \
  2>&1 | tee "${LOG_FILE}"
