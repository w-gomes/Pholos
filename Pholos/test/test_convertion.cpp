#include "catch.hpp"

TEST_CASE("Basic test", "[basic]") {
  int number{0};
  REQUIRE(number == 0);
}
