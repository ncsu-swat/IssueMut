# IssueMut Mutator Integration Instructions

This document provides step-by-step instructions for setting up and running the IssueMut mutators with two fuzzing frameworks: MetaMut and Kitten.
A Docker image is available with all mined mutators and pre-configured metamut_i and kitten_i: `docker pull issuemut/issuemut:latest`

- [MetaMut Integration](#metamut-integration)
- [Kitten Integration](#kitten-integration)

## MetaMut Integration

### 1. Clone the Repository of MetaMut
```bash
# Clone the repository
git clone https://github.com/icsnju/MetaMut.git
cd MetaMut
git checkout 2284f81534954fdf1763c0ce6a12441b7394f02e
```

### 2. Apply the Patch

The `metamut_i.patch` is located in the `metamut_i` folder.
```bash
# Apply the patch file
git apply ../metamut_i.patch
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

### 5. Copy Mutators into MetaMut Framework

From `mined_data/gcc/mutators` and `mined_data/llvm/mutators` folders, please copy:
- Mutator C++ files (`.cpp`) to `mutators/<mutator_set_folder>`
- Mutator bash scripts (`.sh`) to `mutators/scripts`

### 6. Build the Mutators

Before building, please edit `CMakeLists.txt` to add your mutator executable with the designated path.
```bash
cd mutators
mkdir output
cd output

# Configure with CMake
cmake .. -DLLVM_CONFIG_BINARY=$(which llvm-config-12)

# Build with Make
make -j$(nproc)
```

### 7. Extract and Prepare the Seeds
```bash
cd MetaMut/
# Extract the seed corpus
tar -xzf ../../data/seeds.tar.gz
```

### 8. Install Required Packages for Fuzzer
```bash
sudo apt-get install -y flex bison yacc
sudo apt-get install libllvm15 libclang-15-dev llvm-15-tools
sudo apt-get install gcc-11 g++-11 gcc-11-plugin-dev
sudo pip3 install sysv_ipc numpy psutil six
sudo update-alternatives --install /usr/bin/llvm-config llvm-config $(which llvm-config-12) 999999
```

### 9. Run the Fuzzer

Before running the fuzzer, please check which mutator executable you wish to use in `MetaMut/fuzzer/configs.py`.

Run the fuzzer for a test run for 5 minutes.
```bash
bash test_run.sh  # uses 10 cores
```

Run the fuzzer for 5 times (each run lasts 24h).
```bash
bash exp_run.sh  # uses 30 cores
```

## Kitten Integration

### 1. Clone the Repository of Kitten
```bash
# Clone the repository
git clone https://github.com/uw-pluverse/perses.git
cd perses
git checkout 2284f81534954fdf1763c0ce6a12441b7394f02e
```

### 2. Apply the Patch

The `kitten_i.patch` is located in the `kitten_i` folder.
```bash
# Apply the patch file
git apply ../kitten_i.patch
```

### 3. Copy the Execution Scripts

Copy the provided scripts to your workspace folder (replace `/your/workspace/` with your actual workspace path).
```bash
cp kitten_i/* perses/kitten/your/workspace/
```

### 4. Build kitten_i
```bash
bash compile.sh
```

### 5. Setup Configs

Edit `config.yaml` to set your seed folder path and installed compiler path.

### 6. Run the Fuzzer

Run the fuzzer for a test run for 5 minutes.
```bash
bash test_run.sh
```

(Slurm) Run the fuzzer for the experiment — kitten and kitten_i each run 50 times in parallel (each run lasts 8h).
```bash
bash exp_runs.sh
```