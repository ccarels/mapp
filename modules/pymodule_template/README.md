# MAPP - Modular Analysis Pipeline Processor
## pymodule_template
## Download and Install
### Download
Download the source code from GitHub
```
git clone ...
```
### Install
#### Pre-requisites
The following packages are required

| Package | Minimum version | Notes
| :----- | -----: | :----- |
| `core` | | And dependencies thereof |

#### Installation

    mkdir -p build && cd build/
    cmake -DMAPP_CORE_PATH=/absolute/path/to/mapp/core -DMAPP_DATA_MODELS_PATH=/absolute/path/to/data_models/ ../
    make

The absolute paths shown above should be substituted with those on your own system.
The aforementioned CMake variables can also be set as environment variables instead.
To enable documentation, set `-DDOCS=ON`.

#### View documentation
To view the documentation after compilation, open

    ./doc/html/index.html

### Tests
A number of tests can be run during development.
#### Pre-requisites
In addition to the installation pre-requisites,
the following packages are required

| Package | Minimum version | Notes
| :----- | -----: | :----- |
| lcov | 1.14 | |

#### Run C/C++ tests
To compile the unit tests and to produce coverage test results

    cd tests/coverage && mkdir -p build && cd build/
    cmake -DMAPP_CORE_PATH=/absolute/path/to/mapp/core -DMAPP_DATA_MODELS_PATH=/absolute_path/to/mapp/data_models/ -DCONFIG_DATA_MODEL_LIB=/absolute/path/to/mapp/data_models/pymodule_template/build/libpymodule_template_config_data_model.so -DMODULE_LIB=/absolute/path/to/mapp/modules/pymodule_template/build/libpymodule_template.so ../
    make && make test && make lcov

The absolute paths shown above should be substituted with those on your own system.
The aforementioned CMake variables can also be set as environment variables instead.

#### View C/C++ test results
To view the output of the coverage tests, open

    ./lcoverage/index.html

### Benchmark Tests
#### Pre-requisites
In addition to the installation pre-requisites,
the following packages are required

| Package | Minimum version | Notes
| :----- | -----: | :----- |
| benchmark | 1.5.4 | Google Benchmark library |
#### Run C/C++ benchmarks
To compile and run the benchmarks

    cd tests/benchmarks && mkdir -p build && cd build/
    cmake -DMAPP_CORE_PATH=/absolute/path/to/mapp/core/ -DMAPP_DATA_MODELS_PATH=/absolute/path/to/mapp/data_models/ -DMODULE_LIB=/absolute/path/to/mapp/modules/pymodule_template/build/libpymodule_template.so ../
    make
    ./test_benchmark_mapp_core

The absolute paths shown above should be substituted with those on your own system.
The aforementioned CMake variables can also be set as environment variables instead.
