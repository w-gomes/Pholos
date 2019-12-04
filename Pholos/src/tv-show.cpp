#include "tv-show.hpp"

namespace Pholos {

TvShow::TvShow(std::string name) : name_(std::move(name)) {}

TvShow::TvShow(std::string name, std::string alias)
    : name_(std::move(name)), alias_(std::move(alias)) {}

TvShow::TvShow(std::string name, int year, double rating, std::map<int, int> season, Stats stats)
    : name_(std::move(name)), year_(year), rating_(rating), season_{season}, stats_{stats} {}

TvShow::TvShow(std::string name, int year, double rating, std::map<int, int> season, Stats stats,
               std::string alias)
    : name_(std::move(name))
    , year_(year)
    , rating_(rating)
    , season_{season}
    , stats_{stats}
    , alias_{alias} {}

std::string TvShow::get_name() const { return this->name_; }

int TvShow::get_year() const { return this->year_; }

double TvShow::get_rating() const { return this->rating_; }

std::string TvShow::get_stats() const {
  std::string stats;
  switch (this->stats_) {
    case Stats::PlanToWatch:
      stats = "Plan to watch";
      break;
    case Stats::Watching:
      stats = "Watching";
      break;
    case Stats::Completed:
      stats = "Completed";
      break;
    case Stats::Dropped:
      stats = "Dropped";
      break;
    case Stats::NotSet:
      stats = "Not set";
      break;
  }

  return stats;
}

std::map<int, int> TvShow::get_seasons() const { return this->season_; }

std::string TvShow::get_alias() const { return this->alias_; }

void TvShow::set_name(const std::string &name) { this->name_ = name; }

void TvShow::set_year(int year) { this->year_ = year; }

void TvShow::set_rating(double rating) { this->rating_ = rating; }

void TvShow::set_stats(int response) {
  switch (static_cast<Stats>(response)) {
    case Stats::NotSet:
      this->stats_ = Stats::NotSet;
      break;
    case Stats::PlanToWatch:
      this->stats_ = Stats::PlanToWatch;
      break;
    case Stats::Watching:
      this->stats_ = Stats::Watching;
      break;
    case Stats::Completed:
      this->stats_ = Stats::Completed;
      break;
    case Stats::Dropped:
      this->stats_ = Stats::Dropped;
      break;
    default:
      break;
  }
}

void TvShow::add_season(int season, int episode) { this->season_.insert({season, episode}); }

void TvShow::set_alias(const std::string &alias) { this->alias_ = alias; }
}  // namespace Pholos
