#pragma once

/* entertainment.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <string>
#include <string_view>

#include "Stats.hpp"

namespace Pholos {
class Entertainment {
 public:
  Entertainment() = default;

  virtual std::string name() const           = 0;
  virtual double rating() const              = 0;
  virtual int stat() const                   = 0;
  virtual std::string stat_to_string() const = 0;

  virtual ~Entertainment() = default;

 protected:
  void set_members(const std::string &name, double rating, int stat);

  std::string name_{};
  double rating_{};
  Stats stat_{};
};
}  // namespace Pholos
