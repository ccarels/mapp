#ifndef status_code_hpp
#define status_code_hpp

#include <vector>

namespace mapp::core {
/**
 * \enum status_code
 * \brief Generic status codes.
 */
enum class status_code : int { success, failure };

/**
 * \struct status
 * \brief Because \ref mapp::core::algorithm::processor encapsulates the behaviors of algorithms performing potentially many tasks; the ability to have more than one \ref mapp::core::status_code can provide more detailed information.
 */
struct status { std::vector<mapp::core::status_code> code; };

}  // namespace mapp::core

#endif
