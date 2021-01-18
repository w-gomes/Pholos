#pragma once

/* content-base.hpp - Abstract class for Movies, TvShow, Anime
 *
 */

#include <string>

namespace Pholos {

class ContentBase {
 public:
  ContentBase() = default;

  [[nodiscard]] virtual auto name() const -> std::string           = 0;
  [[nodiscard]] virtual auto rating() const -> double              = 0;
  [[nodiscard]] virtual auto stat() const -> int                   = 0;
  [[nodiscard]] virtual auto stat_as_string() const -> std::string = 0;

  auto change_stat(int new_stat) -> void;
  auto change_rating(double new_rating) -> void;
  auto change_name(const std::string &new_name) -> void;

  virtual ~ContentBase() = default;

 protected:
  enum class Stats {
    NotSet      = -1,
    Watching    = 1,
    PlanToWatch = 2,
    Completed   = 3,
    Dropped     = 4
  };

  auto set_members(std::string name, double rating, int stat) -> void;

  std::string name_{};
  double rating_{};
  Stats stat_{};
};
}  // namespace Pholos
