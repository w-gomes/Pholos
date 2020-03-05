#include <limits>
#include <type_traits>

#include "catch.hpp"
#include "common.hpp"

TEST_CASE("Testing basic convertion", "[convertion]") {
  std::size_t small_number = 5032020;
  auto new_number          = Pholos::common::convert<std::size_t, unsigned long>(small_number);

  REQUIRE(small_number == new_number);
}

TEST_CASE("Testing the convertion from std::size_t to unsigned long long", "[convertion]") {
  using namespace Pholos;
  using namespace common;
  auto name           = std::string("Wallace");
  std::size_t my_id_1 = generate_id(name);
  auto my_id_2        = convert<std::size_t, unsigned long long>(my_id_1);

  REQUIRE(my_id_1 == my_id_2);

  SECTION("Checks if types are the same") {
    REQUIRE(std::is_same<unsigned long long, decltype(my_id_2)>::value == true);
  }
}

TEST_CASE("Testing the convertion from unsigned long long to std::size_t", "[convertion]") {
  using namespace Pholos;
  using namespace common;
  unsigned long long big_number = std::numeric_limits<unsigned long long>::max();

  auto other_big_number = convert<unsigned long long, std::size_t>(big_number);

  REQUIRE(big_number == other_big_number);

  SECTION("Checks if types are the same") {
    REQUIRE(std::is_same<unsigned long long, decltype(other_big_number)>::value == true);
  }
}
