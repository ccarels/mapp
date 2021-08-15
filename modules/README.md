# MAPP - Modular Analysis Pipeline Processor

## Modules
Each module should be placed in its own folder following the example code shown in the `mymodule` module.

A `module` conforms to `core` interfaces.
After a `module` is compiled as a shared object library file, the `core` can dynamically load and execute the `module`.

To get started, make a copy of the entire `mymodule` directory.
File names or directory names do not have to be changed, but consider giving the module a different name to help distinguish it.
Do so by editing line 12 in `mymodule/src/mymodule.hpp`

    #define MODULE_NAME_STRING "mymodule"

substituting `mymodule` with a new module name (leave the quotation marks in place).
This is the name the module will use to identify itself at runtime.

To rename the library object, edit line 2 in `CMakeLists.txt` and change the project name

    project(mymodule VERSION 0.0.0 DESCRIPTION "mymodule")

If the module has any additional dependencies, add them in `CMakeLists.txt`.
