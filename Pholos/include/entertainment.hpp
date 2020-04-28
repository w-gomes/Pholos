#pragma once

/* entertainment.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <string>
#include <string_view>

#include "Stats.hpp"

namespace Pholos {
class Entertainment {
 public:
  Entertainment() = default;

  // Debug
  virtual void print() = 0;

  virtual std::string name() const = 0;
  virtual double rating() const    = 0;
  virtual int stat() const         = 0;

  virtual ~Entertainment() = default;

 protected:
  void set_members(const std::string &name, double rating, int stat);
  std::string_view stat() {
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

  std::string name_{};
  double rating_{};
  Stats stat_{};
};
}  // namespace Pholos
