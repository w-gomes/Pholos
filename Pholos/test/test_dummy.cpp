#include "catch2/catch.hpp"

TEST_CASE("Dummy test", "[Dummy]") {
  const int dummy = 20;
  REQUIRE(dummy == 20);
}

TEST_CASE("Ok dude", "[okdude]") {
  const int dummy = 10;
  REQUIRE_FALSE(dummy == 1);
}
