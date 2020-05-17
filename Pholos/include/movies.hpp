#pragma once

#include <string>

#include "entertainment.hpp"
#include "stats.hpp"

namespace Pholos {

class Movies : public Entertainment {
 public:
  Movies() = default;
  Movies(std::string name, double rating, int stat);

  Movies(const Movies &other) = default;
  Movies &operator=(const Movies &other) = default;

  Movies(Movies &&other) noexcept = default;
  Movies &operator=(Movies &&other) noexcept = default;

  ~Movies() = default;

  std::string stat_as_string() const override;
  std::string name() const override;
  double rating() const override;
  int stat() const override;
};
}  // namespace Pholos
