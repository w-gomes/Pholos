#pragma once
#include <string>

#include "stats.hpp"

namespace Pholos {

class Movies {
  public:
    Movies() = default;

    explicit Movies(std::string name);
    Movies(std::string name, double rating, int year);
    Movies(std::string name, double rating, int year, Stats stats);
    Movies(const Movies &other);
    Movies &operator=(const Movies &other);

    Movies(Movies &&other) noexcept;
    Movies &operator=(Movies &&other) noexcept;

    ~Movies() = default;

    std::string get_name() const;
    int get_year() const;
    double get_rating() const;
    std::string get_stats() const;

    void set_name(const std::string &name);
    void set_stats(int response);
    void set_rating(double rating);
    void set_year(int year);

  private:
    std::string name_{ "None" };
    double rating_{};
    int year_{};
    Stats stats_ = Stats::NotSet;
};
}  // namespace Pholos
