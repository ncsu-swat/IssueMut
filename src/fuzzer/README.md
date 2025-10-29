# IssueMut Install Instructions

This document provides step-by-step instructions for setting up and running the IssueMut mutators.
Since we ran IssueMut mutators on top of MetaMut, please clone MetaMut and apply the patch.

- Note: To run kitten_i, please clone the repository of Kitten (https://github.com/uw-pluverse/perses.git) and apply the `kitten_i.patch` to it.

## Setup Process

### 1. Clone the Repository of MetaMut

```bash
# Clone the repository
git clone https://github.com/icsnju/MetaMut.git
cd MetaMut
git checkout 2284f81534954fdf1763c0ce6a12441b7394f02e
```

### 2. Apply the Patch

```bash
# Apply the patch file
git apply ../issuemut.patch
```

### 3. Install Required Packages for Mutators

```bash
sudo apt-get install gcc-11 g++-11 gcc-11-plugin-dev
sudo apt-get install llvm-12 llvm-12-dev llvm-12-tools libllvm12 libclang-12-dev lld-12
sudo apt-get install cmake gdb gcc g++ python3 python3-pip
sudo apt-get install flex yacc bison libdw-dev
```

### 4. Run the Setup Script

The setup script will install the compilers that we used in the experiment.

```bash
bash setup.sh
```

### 5. Build the Mutators
Before building the mutators, please copy the mutators from data/ folder.

```bash
cd mutators
mkdir output
cd output

# Configure with CMake
cmake .. -DLLVM_CONFIG_BINARY=$(which llvm-config-12)

# Build with Make
make -j$(nproc)
```

### 6. Extract and Prepare the Seeds

```bash
cd MetaMut/
# Extract the seed corpus
tar -xzf ../../data/seeds.tar.gz
```

### 7. Install Required Packages for Fuzzer

```bash
sudo apt-get install -y flex bison yacc
sudo apt-get install libllvm15 libclang-15-dev llvm-15-tools
sudo apt-get install gcc-11 g++-11 gcc-11-plugin-dev
sudo pip3 install sysv_ipc numpy psutil six
sudo update-alternatives --install /usr/bin/llvm-config llvm-config $(which llvm-config-12) 999999
```

### 8. Run the Fuzzer
Run the fuzzer for once
```bash
mkdir -p workspace; cd workspace
python3 ../fuzzer/run.py -j 120 \
  --wdir $(pwd) \
  --repeat-times 60 \
  --duration 28800 \
  --seeds-dir $(pwd)/../seeds \
  --cc-opt=-O2
```
Run the fuzzer for 5 times
```bash
bash run.sh
```