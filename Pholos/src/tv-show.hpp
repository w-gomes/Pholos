#pragma once

#include <string>
#include <utility>

#include "content-base.hpp"

namespace Pholos {

struct TvShow : ContentBase<TvShow> {
  std::string name_{};
  double rating_{};
  Stats stat_{};
  int episode_{};
  int last_episode_{};

  TvShow(
    std::string name, double rating, int stat, int episode, int last_episode)
    : name_(std::move(name))
    , rating_(rating)
    , stat_(static_cast<Stats>(stat))
    , episode_(episode)
    , last_episode_(last_episode) {}

  TvShow(const TvShow &other) = default;
  TvShow(TvShow &&other)      = default;
  TvShow &operator=(const TvShow &other) = default;
  TvShow &operator=(TvShow &&other) = default;
  ~TvShow()                         = default;
};
}  // namespace Pholos
