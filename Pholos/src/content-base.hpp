#pragma once

/* content-base.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <string>

namespace Pholos {

class ContentBase {
 public:
  ContentBase() = default;

  virtual std::string name() const           = 0;
  virtual double rating() const              = 0;
  virtual int stat() const                   = 0;
  virtual std::string stat_as_string() const = 0;

  void change_stat(int new_stat);
  void change_rating(double new_rating);
  void change_name(const std::string &new_name);

  virtual ~ContentBase() = default;

 protected:
  enum class Stats {
    NotSet      = -1,
    Watching    = 1,
    PlanToWatch = 2,
    Completed   = 3,
    Dropped     = 4
  };

  void set_members(std::string name, double rating, int stat);

  std::string name_{};
  double rating_{};
  Stats stat_{};
};
}  // namespace Pholos
