#pragma once

#include <string>

#include "entertainment.hpp"
#include "stats.hpp"

namespace Pholos {

class TvShow : public Entertainment {
 public:
  TvShow() = default;

  TvShow(std::string name, int stat, double rating, int episode, int last_episode);

  TvShow(const TvShow &other) = default;
  TvShow &operator=(const TvShow &other) = default;

  TvShow(TvShow &&obj) noexcept = default;
  TvShow &operator=(TvShow &&obj) noexcept = default;

  ~TvShow() = default;

  std::string stat_as_string() const override;
  std::string name() const override;
  double rating() const override;
  int stat() const override;
  int episode() const;
  int last_episode() const;

  void change_episose(int episode);
  void change_last_episode(int last_episode);

 private:
  int episode_{};
  int last_episode_{};
};
}  // namespace Pholos
