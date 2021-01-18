#pragma once

namespace Pholos::internal {

#define FWD(x) static_cast<decltype(x) &&>(x)

// Add helper function that calls constructor of either
// Movies or TvShow
template <typename Context, typename... Types>
Context add_context(Types &&...type) {
  return Context(FWD(type)...);
}
}  // namespace Pholos::internal
