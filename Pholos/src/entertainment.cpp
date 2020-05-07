#include "entertainment.hpp"

namespace Pholos {
void Entertainment::set_members(const std::string &name, double rating, int stat) {
  this->name_   = name;
  this->rating_ = rating;
  this->stat_   = static_cast<Stats>(stat);
}

void Entertainment::change_stat(int new_stat) {
  // TODO: Handle index out of the range.
  this->stat_ = static_cast<Stats>(new_stat);
}

void Entertainment::change_rating(double new_rating) { this->rating_ = new_rating; }

void Entertainment::change_name(const std::string &new_name) { this->name_ = new_name; }
}  // namespace Pholos
