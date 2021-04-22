#pragma once

/* content-base.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <concepts>
#include <string>

#include "constants.hpp"

namespace Pholos {

struct Movies;
struct TvShow;

template <typename Derived>
class ContentBase {
  ContentBase() = default;
  friend Derived;

  [[nodiscard]] Derived &derived() { return static_cast<Derived &>(*this); }
  [[nodiscard]] Derived const &derived() const {
    return static_cast<Derived const &>(*this);
  }

 public:
  [[nodiscard]] auto stat_as_string() const -> std::string {
    auto &self = this->derived();
    switch (self.stat_) {
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

  [[nodiscard]] auto name() const -> std::string {
    return this->derived().name_;
  }

  [[nodiscard]] auto rating() const -> double {
    return this->derived().rating_;
  }

  [[nodiscard]] auto stat() const -> int {
    auto &self = this->derived();
    return static_cast<int>(self.stat_);
  }

  [[nodiscard]] auto episode() const
    -> int requires std::same_as<Derived, TvShow> {
    return this->derived().episode_;
  }

  [[nodiscard]] auto last_episode() const
    -> int requires std::same_as<Derived, TvShow> {
    return this->derived().last_episode_;
  }
};

}  // namespace Pholos
