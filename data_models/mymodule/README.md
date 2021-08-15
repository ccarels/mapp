# MAPP - Modular Analysis Pipeline Processor - Data Models

## data_models/mymodule
First compile the `.proto` file

    protoc --cpp_out=./generated/cpp/ --python_out=./generated/py/ ./mymodule_config_data_model.proto 

Then compile the generated code into a shared object library

    mkdir -p build && cd build
    cmake ../ && make
