#include "content-base.hpp"

#include <utility>

namespace Pholos {
auto ContentBase::set_members(std::string name, double rating, int stat)
  -> void {
  this->name_   = std::move(name);
  this->rating_ = rating;
  this->stat_   = static_cast<Stats>(stat);
}

auto ContentBase::change_stat(int new_stat) -> void {
  // TODO: Handle index out of the range.
  this->stat_ = static_cast<Stats>(new_stat);
}

auto ContentBase::change_rating(double new_rating) -> void {
  this->rating_ = new_rating;
}

auto ContentBase::change_name(const std::string &new_name) -> void {
  this->name_ = new_name;
}
}  // namespace Pholos
