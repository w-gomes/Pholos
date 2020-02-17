#include <utility>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
namespace common {

template <typename... Types>
auto add_movie(Types &&... type) {
  return Movies(std::forward<Types>(type)...);
}
}  // namespace common
}  // namespace Pholos
