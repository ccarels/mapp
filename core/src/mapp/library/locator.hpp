#ifndef locator_hpp
#define locator_hpp

#include <sys/stat.h>

#include <algorithm>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace mapp::core::library {
/**
 * \class locator
 * \brief A locator class that enables finding the paths on disk to dynamic shared object library (.so) files for configured named modules.
 */
class locator final {
 public:
  locator() noexcept = default;
  ~locator() noexcept = default;

  /**
   * \struct lib
   * \brief The name and location of a dynamic shared object library (.so) file on disk.
   */
  struct lib {
    std::string name; /**< \brief The name of a module as a std::string containing only UTF-8 characters. */
    std::string path; /**< \brief The absolute path to a dynamic shared object library (.so) file on disk as a std::string containing only UTF-8 characters.*/
  };

  /**
   * \brief Load and parse a text file on disk that contains the names of modules and the paths to the corresponding dynamic shared object library (.so) files on disk.
   * Each line of the text file contains: 1. The all-lowercase unique name of the module (no spaces) as a std::string containing only UTF-8 characters; 2. A single space; 3. The absolute path to the dynamic shared object library (.so) file on disk as
   * a std::string containing only UTF-8 characters - paths with spaces will be concatenated to a single path and may not contain the backslash (\) escape character.
   * The modules and paths are stored within instances of this class as \ref lib objects which are accessible through the \ref name method.
   * \param path The absolute path as a std::string to the configuration text file that contains the names of modules and the paths to their respective dynamic shared object library (.so) files on disk.
   */
  void load_config_file(const std::string& path) {
    std::string l;
    std::ifstream i(path.c_str());
    if (i.is_open()) {
      while (getline(i, l)) {
        std::regex space("\\s+");
        std::vector<std::string> r{std::sregex_token_iterator(l.begin(), l.end(), space, -1), {}};
        if(r.size() < 2) { continue; } // Skip incomplete entries
        // r.at(0) is the module name, r.at(1) and above is the path
        // Concatenate all elements beyond index 1 to the path variable,
        // in case there are spaces in the path.
        for (std::size_t j = 2; j < r.size(); j++) { r.at(1) += " " + r.at(j); }

        std::for_each(r.at(0).begin(), r.at(0).end(), [](char& c) { c = static_cast<char>(::tolower(c)); });

        lib tmp = {r.at(0), ""};
        if ((std::find_if(_libs.begin(), _libs.end(), [&t = tmp](const lib& tt) -> bool { return t.name == tt.name; }) == _libs.end()) && path_exists(r.at(1))) {
          _libs.push_back({r.at(0), r.at(1)});
        }
      }
      i.close();
    }
    else { throw std::invalid_argument("File \"" + path + "\" cannot be opened. You probably did not specify a path to a suitable configuration file."); }
  }

  /**
   * \brief Look for the \ref lib information for a module by specifying its name.
   * \param name The name of the module as a std::string.
   * \return On success (the module was found), the returned \ref lib object contains the module name and absolute path on disk to the named dynamic shared object library. On failure (the module was not found), the returned \ref lib object contains
   * the provided name but the path std::string is empty.
   */
  [[nodiscard]] auto name(const std::string& name) const -> const lib {
    lib tmp = {name, ""};
    auto it = std::find_if(_libs.begin(), _libs.end(), [&t = tmp](const lib& tt) -> bool { return t.name == tt.name; });
    return (it != _libs.end()) ? *it : tmp;
  }

  /**
   * \brief Accessor method to the \ref lib information about available modules.
   * \return \ref lib information about all available modules.
   */
  [[nodiscard]] auto lib_info() const -> const std::vector<lib>& { return _libs; }

 private:
  std::vector<lib> _libs;

  static auto path_exists(const std::string& p) -> bool {
    struct stat b {};
    return (stat(p.c_str(), &b) == 0);
  }
};
}  // namespace mapp::core::library

#endif
