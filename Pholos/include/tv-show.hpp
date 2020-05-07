#pragma once

#include <string>

#include "entertainment.hpp"
#include "stats.hpp"

namespace Pholos {

class TvShow : public Entertainment {
 public:
  TvShow() = default;

  TvShow(const std::string &name, int stat, double rating, int episode, int last_episode);

  TvShow(const TvShow &other) = default;
  TvShow &operator=(const TvShow &other) = default;

  TvShow(TvShow &&obj) noexcept = default;
  TvShow &operator=(TvShow &&obj) noexcept = default;

  ~TvShow() = default;

  std::string stat_to_string() const override;
  std::string name() const override;
  double rating() const override;
  int stat() const override;
  int episode() const;
  int last_episode() const;

  // change episode
  // change last episode

 private:
  int episode_{};
  int last_episode_{};
};
}  // namespace Pholos
