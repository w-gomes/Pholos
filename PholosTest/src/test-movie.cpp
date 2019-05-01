// test-movie.cpp
#include "catch/catch.hpp"

#include <type_traits>

#include "Movie.hpp"

using namespace Pholos;

class MoviesTest : public Movies {
   public:
    MoviesTest()
        : Movies()
    {
    }
};

TEST_CASE("Vector creation", "[vector]")
{
    std::vector<int> v(5);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
}

TEST_CASE("Object creation", "[Movies]")
{
    MoviesTest movie;
    SECTION("Testing")
    {
        REQUIRE(std::is_base_of<Movies, MoviesTest>::value == true);
    }
}
