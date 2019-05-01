#include "Movie.hpp"

namespace Pholos {

Movies::Movies(const std::string &name, double rating, int year, Stats stats = Stats::PlanToWatch)
    : name_(name)
    , rating_(rating)
    , year_(year)
    , stats_(stats)
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

Movies::Stats Movies::getStats() const
{
    return this->stats_;
}

// TODO:
// This function should take a parameter and change
// the movie stats
// Don't forget: If you want to compare int to enum class
// You have to static_cast<Stats>(value)
void Movies::setStats()
{
}

}  // namespace Pholos
