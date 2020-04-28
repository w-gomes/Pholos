#include "movies.hpp"

#include <string>

#include "fmt/core.h"

namespace Pholos {
Movies::Movies(const std::string &name, double rating, int stat) {
  this->set_members(name, rating, stat);
}

void Movies::print() {
  fmt::print("Name: {} | Rating: {} | Stat: {}", this->name_, this->rating_, this->stat());
}

std::string Movies::name() const { return this->name_; }

double Movies::rating() const { return this->rating_; }

int Movies::stat() const { return static_cast<int>(this->stat_); }
}  // namespace Pholos
