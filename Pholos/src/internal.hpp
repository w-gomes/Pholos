#pragma once

#include <string>
#include <utility>

namespace Pholos {

namespace internal {
// Add helper function that calls constructor of either
// Movies or TvShow
template <typename Context, typename... Types>
Context add_context(Types &&... type) {
  return Context(std::forward<Types>(type)...);
}
}  // namespace internal
}  // namespace Pholos
