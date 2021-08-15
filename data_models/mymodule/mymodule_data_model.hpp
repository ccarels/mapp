#ifndef mymodule_data_model_hpp
#define mymodule_data_model_hpp

#include <string>

#include "mapp/model/data_model_interface.hpp"

namespace mapp::model {
    class mymodule_data_model : public mapp::core::model::data_model { // Examples: bufferable, gpu, gpu_chunkable, networked
        public:
        struct output {
            int var;
        };

        std::shared_ptr<output> _output;
    };
}

#endif
