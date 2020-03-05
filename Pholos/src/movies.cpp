#include "movies.hpp"

namespace Pholos {

Movies::Movies(std::string name) : name_(std::move(name)) {}

Movies::Movies(std::string name, std::string alias)
    : name_(std::move(name)), alias_(std::move(alias)) {}

Movies::Movies(std::string name, double rating, int year)
    : name_(std::move(name)), rating_(rating), year_(year), stats_(Stats::NotSet) {}

Movies::Movies(std::string name, double rating, int year, Stats stats)
    : name_(std::move(name)), rating_(rating), year_(year), stats_(stats) {}

Movies::Movies(std::string name, double rating, int year, Stats stats, std::string alias)
    : name_(std::move(name))
    , rating_(rating)
    , year_(year)
    , stats_(stats)
    , alias_(std::move(alias)) {}

Movies::Movies(std::string name, double rating, int year, std::string alias)
    : name_(std::move(name)), rating_(rating), year_(year), alias_(std::move(alias)) {}

std::string Movies::get_name() const { return this->name_; }

int Movies::get_year() const { return this->year_; }

double Movies::get_rating() const { return this->rating_; }

std::string Movies::get_alias() const { return this->alias_; }

unsigned long long Movies::get_id() const { return this->ID_; }

void Movies::set_id(unsigned long long id) { this->ID_ = id; }

void Movies::set_name(const std::string &name) { this->name_ = name; }

void Movies::set_alias(const std::string &alias) { this->alias_ = alias; }

std::string Movies::get_stats() const {
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

void Movies::set_stats(int response) {
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

void Movies::set_rating(double rating) { this->rating_ = rating; }

void Movies::set_year(int year) { this->year_ = year; }

}  // namespace Pholos
