#pragma once

#include <string>

#include "content-base.hpp"

namespace Pholos {

class Movies : public ContentBase {
 public:
  Movies() = default;
  Movies(std::string name, double rating, int stat);

  Movies(const Movies &other) = default;
  Movies &operator=(const Movies &other) = default;

  Movies(Movies &&other) noexcept = default;
  Movies &operator=(Movies &&other) noexcept = default;

  ~Movies() override = default;

  [[nodiscard]] std::string stat_as_string() const override;
  [[nodiscard]] std::string name() const override;
  [[nodiscard]] double rating() const override;
  [[nodiscard]] int stat() const override;
};
}  // namespace Pholos
