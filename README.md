# MAPP - Modular Analysis Pipeline Processor

## Introduction
The goal of this project is to deliver a high-performance pipeline software framework that is:

* **Scalable** - it runs on a desktop and/or HPC centres on multiple nodes.
* **Reliable** - it has a user-friendly API, no memory leaks, minimal memory allocations, and it is thoroughly tested.
* **Portable** - it runs on multiple platforms both in a bare metal or containerized environment.
* **Documented** - it has complete user and developer documentation.

Most importantly, the framework should simplify the development process by supporting it in the following ways:

* Separate algorithm and module development from execution flow
* Decouple processing modules from data models
* Enforce clearly defined data structures and interfaces
* Processing modules are plug-and-play
* Bridge C/C++ code and Python code
* Rely on a minimum of third-party dependencies, as necessary.

The framework is implemented under the `core` folder.

## Summary
A brief, high-level overview of the project:

* The code is implemented with modern C++, and Python 3.8 in mind.
* All code should compile without warnings.
* Fully documented with DOxygen comments.
* Tested with about a dozen or so analyzers and tools.
* The code is containerized.
* Pipelines of processing modules can run as C++ or Python, in order to facilitate integration of different code projects into a single, unified pipeline.
* Coverage tests should achieve 100% coverage.
* The code is extensively benchmarked.

The project components and their functionality are as follows

| Component | Functionality |
| :----- | :----- |
| `core` | Module interfaces <br> Python wrapper code <br> File system <br> Dynamic library management <br> Data transport <br> Pipeline scheduling <Logging> |
| `modules` | Implementation of core interfaces <br> Perform useful computational work <br> Links against `core` and `data_models` |
| `data_models` | Data structures and their behaviours <br> Google Protocol buffer files <br> Data format converters <br> Links against `core` |
| `pipelines` | Scripting and executing pipelines modules |

You may wish to consider treating each sub-folder as a separate repository for your own projects.

Refer to the `README.md` files in each of the respective sub-folders for more details.
Some `modules` may make use of data models in the `data_models` folder.
If so, please consult the relevant data models and follow the instructions in the relevant `README.md`.
