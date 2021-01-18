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

  [[nodiscard]] auto stat_as_string() const -> std::string override;
  [[nodiscard]] auto name() const -> std::string override;
  [[nodiscard]] auto rating() const -> double override;
  [[nodiscard]] auto stat() const -> int override;
};
}  // namespace Pholos
