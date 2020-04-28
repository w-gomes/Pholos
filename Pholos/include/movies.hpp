#pragma once
#include <iostream>
#include <string>

#include "entertainment.hpp"
#include "stats.hpp"

namespace Pholos {

class Movies : public Entertainment {
 public:
  Movies() = default;
  Movies(const std::string &name, double rating, int stat);

  Movies(const Movies &other) = default;
  Movies &operator=(const Movies &other) = default;

  Movies(Movies &&other) noexcept = default;
  Movies &operator=(Movies &&other) noexcept = default;

  ~Movies() = default;

  void print() override;
  std::string name() const override;
  double rating() const override;
  int stat() const override;
};
}  // namespace Pholos
