#pragma once

#include <string>

namespace Pholos {

class Movies {
   public:
    enum class Stats
    {
        PlanToWatch = 0,
        Watching,
        Completed,
        Dropped
    };

    Movies() = default;
    explicit Movies(const std::string &name, double rating, int year, Stats stats);

    std::string getName() const;
    int getYear() const;
    double getRating() const;
    Stats getStats() const;

    void setStats();

   private:
    std::string name_{ "none" };
    double rating_{ 0.0 };
    int year_{ 0 };
    Stats stats_ = Stats::PlanToWatch;
};
}  // namespace Pholos
