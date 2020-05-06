#include "internal.hpp"

#include <functional>
#include <string>

namespace Pholos {

namespace Internal {
/*
// @Incomplete implementation of formatting output
void format_objects(const std::vector<std::string> &message) {
  // the size of the header and footer should be the size of the longest string
  const int header_and_footer_size = 100;
  // @Incomplete
  const std::string header = fmt::format("{:#^{}}\n", " List of Movies ", header_and_footer_size);
  fmt::print(header);
  for (const auto &msg : message) {
    fmt::print(msg);
  }
  const std::string footer = fmt::format("{:#^{}}", "", header_and_footer_size);
  fmt::print(footer);
}
*/

std::size_t generate_id(const std::string &s) { return std::hash<std::string>{}(s); }
}  // namespace Internal
}  // namespace Pholos
