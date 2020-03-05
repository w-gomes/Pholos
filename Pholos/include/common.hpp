#include <string>
#include <utility>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
namespace common {

// Add helper function that calls constructor of either
// Movies or TvShow
template <typename Context, typename... Types>
Context add_context(Types &&... type) {
  return Context(std::forward<Types>(type)...);
}

std::size_t generate_id(const std::string &s);

// Convert helper function to convert any types.
//
// If we want to convert an object of type std::size_t to unsigned long,
// we call and pass the type we want to convert to like so:
//
// std::size_t my_old_type = 10;
//
// the first template parameter is the original type we want to convert from
// and second parameter is the type we want to convert to.
// auto my_new_type = convert<std::size_t, unsigned long>(my_old_type);
// template parameter From = old_type
// template parameter To = new_type
//
// TODO: Check for narrowing. That is if a type can't fit in the new type we want.
// Use concepts for this.
template <typename From, typename To>
To convert(From from) {
  return static_cast<To>(from);
}
}  // namespace common
}  // namespace Pholos
