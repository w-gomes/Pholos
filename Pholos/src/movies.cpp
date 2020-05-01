#include "movies.hpp"

#include <string>

#include "fmt/core.h"

namespace Pholos {
Movies::Movies(const std::string &name, double rating, int stat) {
  this->set_members(name, rating, stat);
}

std::string Movies::name() const { return this->name_; }

double Movies::rating() const { return this->rating_; }

int Movies::stat() const { return static_cast<int>(this->stat_); }

std::string Movies::stat_to_string() const {
  switch (this->stat_) {
    case Stats::NotSet:
      return "Not Set";
    case Stats::PlanToWatch:
      return "Plan to Watch";
    case Stats::Completed:
      return "Completed";
    case Stats::Dropped:
      return "Dropped";
    default:
      return "Not Set";
  }
}
}  // namespace Pholos
