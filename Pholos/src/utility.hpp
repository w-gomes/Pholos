#include <cctype>  // std::tolower()
#include <concepts>
#include <cstdio>    // std::getchar()
#include <iostream>  // std::cin
#include <string>
#include <string_view>

#include "fmt/format.h"
#include "movies.hpp"
#include "numeric-aliases.hpp"
#include "tv-show.hpp"

namespace Pholos::internal {

template <class T>
concept Movie_Or_TvShow = std::same_as<T, Movies> || std::same_as<T, TvShow>;

// concept for get_user_input utility
template <typename T>
concept A = std::integral<T> || std::floating_point<T> ||
            std::same_as<T, char> || std::same_as<T, std::string>;

template <A Out, bool Consume = false>
auto get_user_input(std::string_view message) -> Out {
  fmt::print("{}", message);
  // if Out is bool -> yes or no question.
  if constexpr (std::is_same_v<Out, bool>) {
    auto value = tl::uchar{};
    std::cin >> value;
    auto out = Out{false};
    if (std::tolower(value) == 'y') { out = true; }
    return out;
    // if Out is a std::string -> name, or any big string.
  } else if constexpr (std::is_same_v<Out, std::string>) {
    auto in  = char{};
    auto out = Out{};
    enum key {
      new_line = 0xA,
    };

    while (in != key::new_line) {
      in = static_cast<char>(std::getchar());
      if (in == key::new_line) { break; }
      out.push_back(in);
    }
    return out;
  } else if constexpr (std::is_arithmetic_v<Out>) {
    auto out = Out{};
    std::cin >> out;
    std::cin.get();  // to consume enter
    return out;
  }
}

}  // namespace Pholos::internal
