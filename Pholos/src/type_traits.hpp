#pragma once
#include <type_traits>

namespace Pholos {
template <class T>
concept Movie_Or_TvShow =
  std::is_same_v<T, Movies> || std::is_same_v<T, TvShow>;
}  // namespace Pholos
