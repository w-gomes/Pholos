#include "tv-show.hpp"

#include <string>
#include <utility>

namespace Pholos {
TvShow::TvShow(std::string name, int stat, double rating, int episode, int last_episode) {
  this->set_members(std::move(name), rating, stat);
  this->episode_      = stat == 3 ? last_episode : episode;
  this->last_episode_ = last_episode;
}

std::string TvShow::name() const { return this->name_; }

double TvShow::rating() const { return this->rating_; }

int TvShow::stat() const { return static_cast<int>(this->stat_); }

int TvShow::episode() const { return this->episode_; }
int TvShow::last_episode() const { return this->last_episode_; }

std::string TvShow::stat_as_string() const {
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

void TvShow::change_episose(int episode) { this->episode_ = episode; }
void TvShow::change_last_episode(int last_episode) { this->last_episode_ = last_episode; }
}  // namespace Pholos
