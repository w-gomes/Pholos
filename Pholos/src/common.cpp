#include "common.hpp"

#include <functional>
#include <iostream>
#include <string>

namespace Pholos {
namespace common {

std::size_t generate_id(const std::string &s) { return std::hash<std::string>{}(s); }
}  // namespace common
}  // namespace Pholos
