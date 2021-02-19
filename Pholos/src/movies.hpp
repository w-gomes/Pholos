#pragma once

#include <string>

#include "content-base.hpp"

namespace Pholos {

struct Movies : ContentBase<Movies> {
  std::string name_{};
  double rating_{};
  Stats stat_{};

  Movies(std::string name, double rating, int stat)
    : name_(std::move(name))
    , rating_(rating)
    , stat_(static_cast<Stats>(stat)) {}

  Movies(const Movies &other) = default;
  Movies(Movies &&other)      = default;
  Movies &operator=(const Movies &other) = default;
  Movies &operator=(Movies &&other) = default;
  ~Movies()                         = default;
};
}  // namespace Pholos
