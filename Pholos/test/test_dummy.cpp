#include "catch.hpp"

TEST_CASE("Dummy test", "[Dummy]") {
  const int dummy = 20;
  REQUIRE(dummy == 20);
}
