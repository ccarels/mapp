# MAPP - Modular Analysis Pipeline Processor

## Introduction and Purpose
`mapp` - Modular Analysis Pipeline Processor (MAPP), is a framework that facilitates
developing C++ modules and running them as pipeline modules in C++ or in Python.

## Usage
This repository contains core framework functionality.
There is an empty module project called `mymodule` to help users get started.

## Supported Operating Systems
`mapp` has been tested to compile and run on the following operating systems

| Operating System | Architecture | Supported | Notes |
| :----- | :----- | :----- | :----- |
| Arch Linux | x86-64 | Yes | See `singularity/arch-linux.def` |
| CentOS 8 | x86-64 | Yes | See `singularity/centos-8.def` |
| Fedora 34 | x86-64 | Yes | See `singularity/fedora-34.def` |
| macOS Big Sur 11.4 | Apple M1 (RISC) | Yes | |
| openSUSE Leap 15.3 | x86-64 | Yes | See `singularity/opensuse.def` |
| Ubuntu 20.04 | x86-64 | Yes | See `singularity/ubuntu-20.04.def` |
| Windows 10 | x86-64 | Yes | |

Refer to the files in the `Notes` column for package installation instructions.

## Download and Install
### Download
Download the source code from GitHub
```
git clone git@github.com:ccarels/mapp.git
```
or

```
git clone https://github.com/ccarels/mapp.git
```

### Install
#### Pre-requisites
The following packages are needed to compile `mapp`

| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| g++ | 9.1.0 | C++20 support required |
| clang | 12.0.5 | Can be used instead of g++ |
| MSVC | 14.29 | Can be used on Windows 10 |
| CMake | 3.12 | |
| Make | 4.2 | |
| Boost | 1.71 | |
| Protobuf | 3.15 | Google Protocol Buffers |
| Python3 | 3.8 | |
| Doxygen | 1.8 | Optional |

For help installing the required packages on your system, consult the commands in the Singularity image definition file in the `singularity/` folder that is relevant to your platform.

The following Python packages are required
| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| pip3 | 21 | |
| sys | | |
| logging | | |
| argparse | 1.4 | |
| protobuf | 3.15 | |

#### Installation

    mkdir -p build && cd build/
    cmake -DDOCS=ON ../ && make

To build without documentation, set `-DDOCS=OFF`.

Or build one of the Singularity images from the `singularity/` directory.

#### View documentation
To view the documentation after compilation, open

    ./doc/html/index.html

#### Build a Docker image
To build the Docker image
```
docker build -f /path/to/dockerfile -t mapp-core
```
Minimum version: Docker version 20.10.7.

#### Build a Singularity image
To build the Singularity image
```
singularity build --fakeroot mapp-core.sif mapp-core.def
```
Minimum version: Singularity version 3.7.3.

### Run the exec-core-test code
The installation results in an executable called `exec-core-test`, which runs a basic pipeline as an example.
Before running the executable, edit the `config.txt` file in the build directory, and add/remove/edit the absolute paths to the modules as appropriate on your system.

```
./exec-core-test
```

### Tests
A number of tests can be run during development.
#### Pre-requisites
In addition to the installation pre-requisites,
the following packages are required for C/C++ code

| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| lcov | 1.14 | |

The following packages are required for Python code
| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| coverage | 5.5 | Use with `pytest` (see below) |
| pytest | 6.2.4 | Use `coverage run -m pytest /absolute/path/to/test_mapp_pipeline.py && coverage html` |

#### Run C/C++ tests
In order to obtain the shared object library (.so) file for the `mymodule` data model that is referred to in the tests outlined below, first do

    cd data_models/mymodule/ && mkdir -p build && cd build
    cmake ../ && make

Then, to compile the unit tests and to produce coverage test results

    cd tests/coverage && mkdir -p build && cd build/
    cmake -DTHROWING_ALGORITHM_LIB=/absolute/path/to/libthrowing_algorithm.so -DMYMODULE_CONFIG_DATA_MODEL_LIB=/absolute/path/to/libmymodule_config_data_model.so ../
    make && make test && make lcov

The absolute paths shown above should be substituted with those on your own system.
The aforementioned CMake variables can also be set as environment variables instead.

#### View C/C++ test results
To view the output of the coverage tests, open

    ./lcoverage/index.html

#### Run Python tests

    cd build/ && coverage run -m pytest test_mapp_pipeline.py && coverage html

#### View Python test results
To view the output of the coverage tests, open

    ./htmlcov/index.html

### Benchmark Tests
#### Pre-requisites
In addition to the installation pre-requisites,
the following packages are required

| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| benchmark | 1.5.4 | Google Benchmark library |

#### Run C/C++ benchmarks
To compile and run the benchmarks

    cd tests/benchmarks && mkdir -p build && cd build/
    cmake ../ && make
    ./test_benchmark_mapp_core

## Linting and formatting
The following tools are used for linting and formatting of C/C++ code
| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| clang-tidy | 10.0.0 | Use ``clang-tidy -checks='cppcoreguidelines-*,performance-*,readibility-*,modernize-*,misc-*,clang-analyzer-*,google-*,-header-filter=.*'`` |
| iwyu | 0.12 | `iwyu_tool -p .` |
| cppcheck | 1.90 | Use `cppcheck --error-exitcode=1 --project=compile_commands.json -q --std=c11` |
| clang-format | 10.0.0 | Use `clang-format -i /absolute/path/to/file` |
| Infer Static Analyzer | 1.1.0 | Use `infer run -- g++ -c /absolute/path/to/file` <br> Or build with `-DCMAKE_EXPORT_COMPILE_COMMANDS=1`, and then use `infer run --compilation-database compile_commands.json` |

The following tools are used for linting and formatting of Python code
| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| autopep8 | 1.5.7 | Use `autopep8 --in-place --aggressive`|

## Profiling tools
The following tools are used for profiling C/C++ code
| Package | Minimum version | Notes |
| :----- | -----: | :----- |
| valgrind | 3.15.0 | Leak check `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./exec-core-test` |
| kcachegrind | 0.8.0 | Call graph `valgrind --tool=callgrind --dump-instr=yes --simulate-cache=yes --collect-jumps=yes --instr-atstart=no --collect-atstart=no ./exec-core-test` |
| helgrind | 3.15.0 | Thread checking `valgrind --tool=helgrind ./exec-core-test` |
| massif-visualizer | 0.7 | Memory usage check `valgrind --tool=massif ./exec-core-test` |
| AMD uProf | | On AMD platforms |
| NVIDIA Visual Profiler | | On NVIDIA platforms |
| NVIDIA NSight Compute | | On NVIDIA platforms |
| NVIDIA NSight Systems (nsys or nsys-ui) | 2021.2.4 | On NVIDIA platforms |
| cuda-memcheck | 10.1 | Use `cuda-memcheck --leak-check full --check-deprecated-instr yes --print-level info --tool memcheck --log-file cuda-memcheck-log.txt ./exec-core-test` and also use `initcheck`, `racecheck`, and `synccheck` |
| nvprof | 10.1 | Use `sudo nvprof ./exec-core-test` |

## License
Please view the LICENSE file in the top-level directory.

## Copyright
Copyright (C) 2021 Cees Carels
