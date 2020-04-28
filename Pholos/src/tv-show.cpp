#include "tv-show.hpp"

#include <string>

#include "fmt/core.h"

namespace Pholos {
TvShow::TvShow(const std::string &name, int stat, double rating, int episode, int last_episode) {
  this->set_members(name, rating, stat);
  this->episode_      = episode;
  this->last_episode_ = last_episode;
}

void TvShow::print() {
  fmt::print("Name: {} | Rating: {} | Stat: {}", this->name_, this->rating_, this->stat());
}

std::string TvShow::name() const { return this->name_; }

double TvShow::rating() const { return this->rating_; }

int TvShow::stat() const { return static_cast<int>(this->stat_); }
}  // namespace Pholos
