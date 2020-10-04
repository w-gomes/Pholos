#include "content-base.hpp"

#include <utility>

namespace Pholos {
void ContentBase::set_members(std::string name, double rating, int stat) {
  this->name_   = std::move(name);
  this->rating_ = rating;
  this->stat_   = static_cast<Stats>(stat);
}

void ContentBase::change_stat(int new_stat) {
  // TODO: Handle index out of the range.
  this->stat_ = static_cast<Stats>(new_stat);
}

void ContentBase::change_rating(double new_rating) {
  this->rating_ = new_rating;
}

void ContentBase::change_name(const std::string &new_name) {
  this->name_ = new_name;
}
}  // namespace Pholos
