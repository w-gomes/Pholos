#pragma once
#include "Movie.hpp"
#include "catch.hpp"

TEST_CASE("Creating a Movie object")
{
    Pholos::Movies movie("Inception", 10.0, 2010, static_cast<Pholos::Movies::Stats>(0));

    REQUIRE(movie.getName() == "Inception");
    REQUIRE(movie.getRating() == 10.0);
    REQUIRE(movie.getYear() == 2010);
}
