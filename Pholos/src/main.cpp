#include "application.hpp"

#include "Movies/movies.hpp"
#include "fmt/fmt.hpp"

using namespace Pholos;

/*
// Testing
void updatingMovie(Movies &m, const std::string &name, double rating, int year, int stat)
{
    m.setName(name);
    m.setRating(rating);
    m.setYear(year);
    m.setStats(stat);
}

void printing(const Movies &obj)
{
    fmt::print("\nName {}, Rating {}, year {}, stats {}.", obj.getName(), obj.getRating(),
               obj.getYear(), obj.getStats());
}
*/

int main()
{
    Application app;
    app.runApplication();

    /*
    // Test
    {
        Movies movie1;
        Movies movie2("Inception", 10.0, 2010);
        Movies movie3(movie2);
        Movies movie4;
        movie4 = movie2;

        printing(movie1);
        printing(movie2);
        updatingMovie(movie1, "Avengers: End Game", 8.2, 2019, 0);
        updatingMovie(movie2, "Inception", 9.2, 2009, 2);
        printing(movie1);
        printing(movie2);
        printing(movie3);
        printing(movie4);
    }
    */
    return 0;
}
