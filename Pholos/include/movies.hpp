#pragma once
#include <string>

#include "stats.hpp"

namespace Pholos {

class Movies {
 public:
  Movies() = default;

  explicit Movies(std::string name);
  explicit Movies(std::string name, std::string alias);

  Movies(std::string name, double rating, int year);
  Movies(std::string name, double rating, int year, Stats stats);
  Movies(std::string name, double rating, int year, Stats stats, std::string alias);
  Movies(std::string name, double rating, int year, std::string alias);

  Movies(const Movies &other) = default;
  Movies &operator=(const Movies &other) = default;

  Movies(Movies &&other) noexcept = default;
  Movies &operator=(Movies &&other) noexcept = default;

  ~Movies() = default;

  unsigned long long get_id() const;
  std::string get_name() const;
  int get_year() const;
  double get_rating() const;
  std::string get_stats() const;
  std::string get_alias() const;

  void set_id(unsigned long long id);
  void set_name(const std::string &name);
  void set_stats(int response);
  void set_rating(double rating);
  void set_year(int year);
  void set_alias(const std::string &alias);

 private:
  unsigned long long ID_{0};
  std::string name_{"None"};
  double rating_{};
  int year_{};
  std::string alias_{"None"};
  Stats stats_ = Stats::NotSet;
};
}  // namespace Pholos
