#include "tv-show.hpp"

namespace Pholos {

TvShow::TvShow(std::string name)
    : name_(std::move(name))
{
}

TvShow::TvShow(std::string name, int year, double rating, std::map<int, int> season,
               Stats stats)
    : name_(std::move(name))
    , year_(year)
    , rating_(rating)
    , season_{ season }
    , stats_{ stats }
{
}

TvShow::TvShow(const TvShow &other)
{
    this->name_   = other.name_;
    this->year_   = other.year_;
    this->rating_ = other.rating_;
    this->stats_  = other.stats_;
    this->season_ = other.season_;
}

TvShow &TvShow::operator=(const TvShow &other)
{
    if (&other != this) {
        this->name_   = other.name_;
        this->year_   = other.year_;
        this->rating_ = other.rating_;
        this->stats_  = other.stats_;
        this->season_ = other.season_;
    }

    return *this;
}

TvShow::TvShow(TvShow &&other) noexcept
{
    this->name_   = other.name_;
    this->year_   = other.year_;
    this->rating_ = other.rating_;
    this->stats_  = other.stats_;
    this->season_ = other.season_;
}

TvShow &TvShow::operator=(TvShow &&other) noexcept
{
    if (&other != this) {
        this->name_   = other.name_;
        this->year_   = other.year_;
        this->rating_ = other.rating_;
        this->stats_  = other.stats_;
        this->season_ = other.season_;
    }

    return *this;
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

std::string TvShow::getStats() const
{
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

void TvShow::addSeason(int season, int episode)
{
    this->season_.insert({ season, episode });
}
}  // namespace Pholos
