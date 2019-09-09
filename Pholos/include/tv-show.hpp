#pragma once

#include <map>
#include <string>
#include <utility>

#include "stats.hpp"

namespace Pholos {

class TvShow {
  public:
    TvShow() = default;
    explicit TvShow(std::string name);
    TvShow(std::string name, int year, double rating, std::map<int, int> season,
           Stats stats);

    TvShow(const TvShow &other);
    TvShow &operator=(const TvShow &other);

    TvShow(TvShow &&obj) noexcept;
    TvShow &operator=(TvShow &&obj) noexcept;

    ~TvShow() = default;

    std::string get_name() const;
    int get_year() const;
    double get_rating() const;
    std::string get_stats() const;
    std::map<int, int> get_seasons() const;

    void set_name(const std::string &name);
    void set_year(int year);
    void set_rating(double rating);
    void set_stats(int response);
    void add_season(int season, int episode);

  private:
    std::string name_{ "None" };
    std::map<int, int> season_{};
    int year_{};
    double rating_{};
    Stats stats_ = Stats::PlanToWatch;
};
}  // namespace Pholos
