#pragma once
#include <string>

#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
struct Query {
  static std::string make_insert_query(const Movies &movie) {
    return fmt::format(Query::insert_movie, movie.name(), movie.rating(),
                       movie.stat());
  }
  static std::string make_insert_query(const TvShow &tvshow) {
    return fmt::format(Query::insert_tvshow, tvshow.name(), tvshow.rating(),
                       tvshow.stat(), tvshow.episode(), tvshow.last_episode());
  }

  inline static const std::string insert_tvshow =
    "INSERT INTO tvshow (name, rating, stats, episode, last_episode) "
    "VALUES "
    "('{0}', {1}, {2}, {3}, {4})";

  inline static const std::string insert_movie =
    "INSERT INTO movies (name, rating, stats) VALUES ('{0}', {1}, {2})";
};
}  // namespace Pholos
