#include "movies.hpp"

#include <string>
#include <utility>

namespace Pholos {
Movies::Movies(std::string name, double rating, int stat) {
  this->set_members(std::move(name), rating, stat);
}

auto Movies::name() const -> std::string { return this->name_; }

auto Movies::rating() const -> double { return this->rating_; }

auto Movies::stat() const -> int { return static_cast<int>(this->stat_); }

auto Movies::stat_as_string() const -> std::string {
  switch (this->stat_) {
    case Stats::NotSet:
      return "Not Set";
    case Stats::Watching:
      return "Watching";
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
