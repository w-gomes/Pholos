#pragma once

#include <map>
#include <string>

#include "stats.hpp"

namespace Pholos {

class TvShow {
 public:
  TvShow() = default;

  explicit TvShow(std::string name);
  explicit TvShow(std::string name, std::string alias);

  TvShow(std::string name, int year, double rating, std::map<int, int> season, Stats stats);
  TvShow(std::string name, int year, double rating, std::map<int, int> season, Stats stats,
         std::string alias);

  TvShow(const TvShow &other) = default;
  TvShow &operator=(const TvShow &other) = default;

  TvShow(TvShow &&obj) noexcept = default;
  TvShow &operator=(TvShow &&obj) noexcept = default;

  ~TvShow() = default;

  unsigned long long get_id() const;
  std::string get_name() const;
  int get_year() const;
  double get_rating() const;
  std::string get_stats() const;
  std::map<int, int> get_seasons() const;
  std::string get_alias() const;

  void set_id(unsigned long long id);
  void set_name(const std::string &name);
  void set_year(int year);
  void set_rating(double rating);
  void set_stats(int response);
  void add_season(int season, int episode);
  void set_alias(const std::string &alias);

 private:
  unsigned long long ID_{0};
  std::string name_{"None"};
  std::map<int, int> season_{};
  int year_{};
  double rating_{};
  std::string alias_{"None"};
  Stats stats_ = Stats::NotSet;
};
}  // namespace Pholos
