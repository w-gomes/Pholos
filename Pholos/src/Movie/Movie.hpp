#pragma once

#include "Stats.hpp"

#include <string>

namespace Pholos {

class MovieController;

class Movies {
   public:
    Movies() = default;
    explicit Movies(const std::string &name, double rating, int year);
    Movies(const Movies &obj)  = delete;
    Movies(const Movies &&obj) = delete;
    ~Movies()                  = default;

    std::string getName() const;
    int getYear() const;
    double getRating() const;
    Stats getStats() const;

    void setName(const std::string &name);
    void setStats(int response);
    void setRating(double rating);
    void setYear(int year);

   private:
    std::string name_{};
    double rating_{};
    int year_{};
    Stats stats_ = Stats::PlanToWatch;
};
}  // namespace Pholos
