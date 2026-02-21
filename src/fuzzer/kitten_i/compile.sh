#!/bin/bash

cd ..

rm kitten_deploy.jar

cd ../

bazel build kitten/src/org/perses/fuzzer:kitten_deploy.jar

cp bazel-bin/kitten/src/org/perses/fuzzer/kitten_deploy.jar kitten/