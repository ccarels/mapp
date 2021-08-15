# MAPP - Modular Analysis Pipeline Processor

## Data models
* Data models should be placed under `data_models`.
* Data models should be defined either as Google Protocol buffer files which should be compiled to all applicable languages (C++ and Python), or as native C++ classes.

* An example of the required build structure is shown in the `mymodule` folder.

* `modules` may include and link against code generated in the `mymodule` folder in order to make use of relevant data structures.
* Any data structures that cross `module` boundaries represent an interface and must be placed in the `data_models` repository.
* If a data structure exists only internally to a `module`, one can place it directly within the `module` project code instead of in the `data_models` repository.
