#include "entertainment.hpp"

namespace Pholos {
void Entertainment::set_members(const std::string &name, double rating, int stat) {
  this->name_   = name;
  this->rating_ = rating;
  this->stat_   = static_cast<Stats>(stat);
}
}  // namespace Pholos
