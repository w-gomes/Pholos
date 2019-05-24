#include "Movie.hpp"

#include <utility>

namespace Pholos {

Movies::Movies(std::string name, double rating, int year)
    : name_(std::move(name))
    , rating_(rating)
    , year_(year)
    , stats_(Stats::PlanToWatch)
{
}

std::string Movies::getName() const
{
    return this->name_;
}

int Movies::getYear() const
{
    return this->year_;
}

double Movies::getRating() const
{
    return this->rating_;
}

void Movies::setName(const std::string &name)
{
    this->name_ = name;
}

std::string Movies::getStats() const
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

void Movies::setStats(int response)
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
        default:
            break;
    }
}

void Movies::setRating(double rating)
{
    this->rating_ = rating;
}

void Movies::setYear(int year)
{
    this->year_ = year;
}

}  // namespace Pholos
