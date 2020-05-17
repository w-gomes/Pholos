#pragma once

/* entertainment.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <string>

#include "Stats.hpp"

namespace Pholos {

class Entertainment {
 public:
  Entertainment() = default;

  virtual std::string name() const           = 0;
  virtual double rating() const              = 0;
  virtual int stat() const                   = 0;
  virtual std::string stat_as_string() const = 0;

  void change_stat(int new_stat);
  void change_rating(double new_rating);
  void change_name(const std::string &new_name);

  virtual ~Entertainment() = default;

 protected:
  void set_members(std::string name, double rating, int stat);

  std::string name_{};
  double rating_{};
  Stats stat_{};
};
}  // namespace Pholos
