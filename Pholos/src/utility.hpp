#include <cctype>  // std::tolower()
#include <concepts>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

#include "fmt/format.h"
#include "movies.hpp"
#include "numeric-aliases.hpp"
#include "tv-show.hpp"

namespace Pholos::internal {

template <class T>
concept Movie_Or_TvShow =
  std::is_same_v<T, Movies> || std::is_same_v<T, TvShow>;

// concept for get_user_input utility
template <typename T>
concept is_good_input = std::is_arithmetic_v<T> || std::is_same_v<T, char> ||
                        std::is_same_v<T, std::string>;

template <is_good_input Out>
Out get_user_input(std::string_view message) {
  fmt::print("{}", message);
  // if Out is bool -> yes or no question.
  if constexpr (std::is_same_v<Out, bool>) {
    auto value = tl::uchar{};
    std::cin >> value;
    Out out{false};
    if (std::tolower(value) == 'y') { out = true; }
    return out;
    // is Out is a std::string -> name, or any big string.
  } else if constexpr (std::is_same_v<Out, std::string>) {
    Out out;
    std::cin.get();  // to consume enter
    std::getline(std::cin, out);
    return out;
  } else if constexpr (std::is_arithmetic_v<Out>) {
    Out out;
    std::cin >> out;
    return out;
  }
}

}  // namespace Pholos::internal
