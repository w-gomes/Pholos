#include "TvShow.hpp"

namespace Pholos {

TvShow::TvShow(const std::string &name)
    : name_(name)
{
}

TvShow::TvShow(const std::string &name, int year, double rating)
    : name_(name)
    , year_(year)
    , rating_(rating)
{
}

std::string TvShow::getName() const
{
    return this->name_;
}

int TvShow::getYear() const
{
    return this->year_;
}

double TvShow::getRating() const
{
    return this->rating_;
}

Stats TvShow::getStats() const
{
    return this->stats_;
}

std::map<int, int> TvShow::getSeasons() const
{
    return this->season_;
}

void TvShow::setName(const std::string &name)
{
    this->name_ = name;
}

void TvShow::setYear(int year)
{
    this->year_ = year;
}

void TvShow::setRating(double rating)
{
    this->rating_ = rating;
}

void TvShow::setStats(int response)
{
    switch (static_cast<Stats>(response)) {
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
    }
}

void TvShow::addSeason(int season, int episode)
{
    this->season_.insert({ season, episode });
}
}  // namespace Pholos
