#include "User.hpp"

namespace Pholos {

Users::Users(std::string name)
    : name_(std::move(name))
{
}

Users::Users(std::string name, std::vector<Movies> &movieList, std::vector<TvShow> &tvShowList)
    : name_(std::move(name))
    , moviesList_(movieList)
    , tvShowList_(tvShowList)
{
}

Users::Users(std::string name, std::vector<Movies> &movieList)
    : name_(std::move(name))
    , moviesList_(movieList)
{
}

Users::Users(std::string name, std::vector<TvShow> &tvShowList)
    : name_(std::move(name))
    , tvShowList_(tvShowList)
{
}

void Users::addName()
{
}

void Users::addMovie()
{
}

void Users::addTvShow()
{
}

}  // namespace Pholos
