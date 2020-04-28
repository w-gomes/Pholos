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

  void print() override;

  std::string name() const override;
  double rating() const override;
  int stat() const override;

 private:
  int episode_{};
  int last_episode_{};
};
}  // namespace Pholos
