#include "user.hpp"

namespace Pholos {

Users::Users(std::string name)
    : name_(std::move(name))
{
}

Users::Users(std::string name, std::vector<Movies> &movieList,
             std::vector<TvShow> &tvShowList)
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

void Users::add_name()
{
}

void Users::add_movie()
{
}

void Users::add_tv_show()
{
}

}  // namespace Pholos
