#pragma once
#include <string>
#include <vector>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
class Users {
  public:
    Users() = default;
    explicit Users(std::string name);
    Users(std::string name, std::vector<Movies> &movieList,
          std::vector<TvShow> &tvShowList);
    Users(std::string name, std::vector<Movies> &movieList);
    Users(std::string name, std::vector<TvShow> &tvShowList);
    ~Users() = default;

    void add_name();
    void add_movie();
    void add_tv_show();

    // Not sure how to implement this
    /*
    friend operator==(const Users &user, const Users &other)
    {
        return user.name_ == other.name_;
    }*/

  private:
    std::string name_{ "No_name" };
    std::vector<Movies> moviesList_;
    std::vector<TvShow> tvShowList_;
};
}  // namespace Pholos
