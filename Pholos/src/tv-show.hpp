#pragma once

#include <string>

#include "content-base.hpp"

namespace Pholos {

class TvShow : public ContentBase {
 public:
  TvShow() = default;

  TvShow(
    std::string name, int stat, double rating, int episode, int last_episode);

  TvShow(const TvShow &other) = default;
  TvShow &operator=(const TvShow &other) = default;

  TvShow(TvShow &&obj) noexcept = default;
  TvShow &operator=(TvShow &&obj) noexcept = default;

  ~TvShow() override = default;

  [[nodiscard]] auto stat_as_string() const -> std::string override;
  [[nodiscard]] auto name() const -> std::string override;
  [[nodiscard]] auto rating() const -> double override;
  [[nodiscard]] auto stat() const -> int override;
  [[nodiscard]] auto episode() const -> int;
  [[nodiscard]] auto last_episode() const -> int;

  auto change_episose(int episode) -> void;
  auto change_last_episode(int last_episode) -> void;

 private:
  int episode_{};
  int last_episode_{};
};
}  // namespace Pholos
