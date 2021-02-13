#pragma once
#include <string>

#include "constants.hpp"
#include "fmt/format.h"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
using namespace std::literals::string_literals;

struct Query {
  /*** Make queries helpers ***/

  /* Insert query for movies */
  static auto make_insert_query(const Movies &movie) {
    return fmt::format(
      Query::insert_movie, movie.name(), movie.rating(), movie.stat());
  }

  /* Insert query for tv shows */
  static auto make_insert_query(const TvShow &tvshow) {
    return fmt::format(Query::insert_tvshow,
                       tvshow.name(),
                       tvshow.rating(),
                       tvshow.stat(),
                       tvshow.episode(),
                       tvshow.last_episode());
  }

  // test
  static auto make_select_query() { return fmt::format("Hello\n"); }

  /* Creates table queries for movies or tvshow. */
  static auto make_create_table_query(Type query_type) {
    switch (query_type) {
      case Type::TvShow:
        return fmt::format(Query::create_table_tvshow, "tvshow");
      case Type::Movie:
        return fmt::format(Query::create_table_movie, "movies");
      case Type::None:
        break;
    }
    return std::string("");
  }

  /*** INSERT QUERIES ***/

  /* INSERT tvshow */
  inline static auto const insert_tvshow =
    "INSERT INTO tvshow (name, rating, stats, episode, last_episode) "
    "VALUES "
    "('{0}', {1}, {2}, {3}, {4})"s;

  /* INSERT movies */
  inline static auto const insert_movie =
    "INSERT INTO movies (name, rating, stats) VALUES ('{0}', {1}, {2})"s;

  /*** SELECT QUERIES ***/

  /* SELECT * from movies */
  inline static auto const select_all_movie = "SELECT * from movies"s;

  /* SELECT * from tvshow */
  inline static auto const select_all_tvshow = "SELECT * from tvshow"s;

  /* SELECT * from movies using stats */
  inline static auto const select_movie_by_stats =
    "SELECT * from movies WHERE stats={}"s;

  /* SELECT * from tvshow using stats */
  inline static auto const select_tvshow_by_stats =
    "SELECT * from tvshow WHERE stats={}"s;

  /*** UPDATE QUERIES ***/

  /* UPDATE name */
  inline static auto const update_name =
    "UPDATE {} SET name='{}' WHERE id_{}={}"s;

  /* UPDATE stat */
  inline static auto const update_stat =
    "UPDATE {} SET stats={} WHERE id_{}={}"s;

  /* UPDATE rating */
  inline static auto const update_rating =
    "UPDATE {} SET rating={} WHERE id_{}={}"s;

  /* UPDATE total episode */
  inline static auto const update_total_episode =
    "UPDATE {} SET last_episode{} WHERE id_{}={}"s;

  /* UPDATE episode */
  inline static auto const update_episode =
    "UPDATE {} SET episode=episode + {} WHERE id_{}={}"s;

  /*** CREATE TABLE QUERIES ***/

  /* CREATE TABLE tvshow */
  inline static auto const create_table_tvshow =
    "CREATE TABLE IF NOT EXISTS {} (`id_tvshow` INTEGER PRIMARY KEY "
    "AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER, `episode`, `last_episode` "
    "INTEGER);"s;

  /* CREATE TABLE movies */
  inline static auto const create_table_movie =
    "CREATE TABLE IF NOT EXISTS {} (`id_movie` INTEGER PRIMARY KEY "
    "AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER);"s;
};
}  // namespace Pholos
