#include "fmt/fmt.hpp"

#include "Application.hpp"

#include "Movie/Movie.hpp"

using namespace Pholos;

// Testing
void updatingMovie(Movies &m, const std::string &name, double rating, int year, int stat)
{
    m.setName(name);
    m.setRating(rating);
    m.setYear(year);
    m.setStats(stat);
}

int main()
{
    Application app;
    app.runApplication();

    // Test
    {
        Movies movie1;
        Movies movie2("Inception", 10.0, 2010);

        fmt::print("\nName {}, Rating {}, year {}, stats {}.", movie1.getName(), movie1.getRating(),
                   movie1.getYear(), movie1.getStats());
        fmt::print("\nName {}, Rating {}, year {}, stats {}.", movie2.getName(), movie2.getRating(),
                   movie2.getYear(), movie2.getStats());

        updatingMovie(movie1, "Avengers: End Game", 8.2, 2019, 0);
        updatingMovie(movie2, "Inception", 9.2, 2009, 2);
        fmt::print("\nName {}, Rating {}, year {}, stats {}.", movie1.getName(), movie1.getRating(),
                   movie1.getYear(), movie1.getStats());
        fmt::print("\nName {}, Rating {}, year {}, stats {}.", movie2.getName(), movie2.getRating(),
                   movie2.getYear(), movie2.getStats());
    }

    return 0;
}
