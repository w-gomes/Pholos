#pragma once
#include <string>

namespace Pholos {
struct Query {
  inline static const std::string insert_tvshow =
    "INSERT INTO tvshow (name, rating, stats, episode, last_episode) "
    "VALUES "
    "('{0}', {1}, {2}, {3}, {4})";

  inline static const std::string insert_movie =
    "INSERT INTO movies (name, rating, stats) VALUES ('{0}', {1}, {2})";
};
}  // namespace Pholos
