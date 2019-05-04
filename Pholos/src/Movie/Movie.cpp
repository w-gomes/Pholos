#include "Movie.hpp"

namespace Pholos {

Movies::Movies(const std::string &name, double rating, int year)
    : name_(name)
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

Stats Movies::getStats() const
{
    return this->stats_;
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