#include "Movie.hpp"
#include "import.hpp"

using namespace Pholos;

int main(int argc, char **argv)
{
    fmt::print("Test\n");
    Movies movie("Inception", 10.0, 2010, static_cast<Movies::Stats>(0));

    std::string name = movie.getName();
    double rating    = movie.getRating();
    int year         = movie.getYear();

    fmt::print("Name: {}, rating: {}, year: {}.", name, rating, year);

    return 0;
}
