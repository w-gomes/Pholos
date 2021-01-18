#include "tv-show.hpp"

#include <string>
#include <utility>

namespace Pholos {
TvShow::TvShow(
  std::string name, int stat, double rating, int episode, int last_episode) {
  this->set_members(std::move(name), rating, stat);
  this->episode_      = stat == 3 ? last_episode : episode;
  this->last_episode_ = last_episode;
}

auto TvShow::name() const -> std::string { return this->name_; }

auto TvShow::rating() const -> double { return this->rating_; }

auto TvShow::stat() const -> int { return static_cast<int>(this->stat_); }
auto TvShow::episode() const -> int { return this->episode_; }
auto TvShow::last_episode() const -> int { return this->last_episode_; }

auto TvShow::stat_as_string() const -> std::string {
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

auto TvShow::change_episose(int episode) -> void { this->episode_ = episode; }
auto TvShow::change_last_episode(int last_episode) -> void {
  this->last_episode_ = last_episode;
}
}  // namespace Pholos
