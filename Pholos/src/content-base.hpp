#pragma once

/* content-base.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <concepts>
#include <string>

namespace Pholos {

struct Movies;
struct TvShow;

template <typename Derived>
class ContentBase {
  enum class Stats {
    NotSet      = -1,
    Watching    = 1,
    PlanToWatch = 2,
    Completed   = 3,
    Dropped     = 4
  };

  static auto stat_to_string(Stats stat) -> std::string {
    switch (stat) {
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

  ContentBase() = default;
  friend Derived;

  Derived &derived() { return static_cast<Derived &>(*this); }
  Derived const &derived() const { return static_cast<Derived const &>(*this); }

 public:
  [[nodiscard]] auto stat_as_string() const -> std::string
    requires std::same_as<Derived, Movies> {
    auto &self = this->derived();
    return ContentBase::stat_to_string(self.stat_);
  }

  [[nodiscard]] auto stat_as_string() const -> std::string
    requires std::same_as<Derived, TvShow> {
    auto &self = this->derived();
    return ContentBase::stat_to_string(self.stat_);
  }

  [[nodiscard]] auto name() const -> std::string
    requires std::same_as<Derived, Movies> {
    return this->derived().name_;
  }

  [[nodiscard]] auto name() const -> std::string
    requires std::same_as<Derived, TvShow> {
    return this->derived().name_;
  }

  [[nodiscard]] auto rating() const
    -> double requires std::same_as<Derived, Movies> {
    return this->derived().rating_;
    ;
  }

  [[nodiscard]] auto rating() const
    -> double requires std::same_as<Derived, TvShow> {
    return this->derived().rating_;
  }

  [[nodiscard]] auto stat() const
    -> int requires std::same_as<Derived, Movies> {
    auto &self = this->derived();
    return static_cast<int>(self.stat_);
  }

  [[nodiscard]] auto stat() const
    -> int requires std::same_as<Derived, TvShow> {
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
