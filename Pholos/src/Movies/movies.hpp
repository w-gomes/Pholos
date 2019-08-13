#pragma once
#include <string>

#include "Stats/stats.hpp"

namespace Pholos {

class Movies {
  public:
    Movies() = default;

    explicit Movies(std::string name);
    Movies(std::string name, double rating, int year);
    Movies(std::string name, double rating, int year, Stats stats);
    Movies(const Movies &other);
    Movies &operator=(const Movies &other);

    Movies(const Movies &&other);
    Movies &operator=(const Movies &&other);

    ~Movies() = default;

    std::string getName() const;
    int getYear() const;
    double getRating() const;
    std::string getStats() const;

    void setName(const std::string &name);
    void setStats(int response);
    void setRating(double rating);
    void setYear(int year);

  private:
    std::string name_{ "None" };
    double rating_{};
    int year_{};
    Stats stats_ = Stats::NotSet;
};
}  // namespace Pholos
