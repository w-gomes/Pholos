#pragma once
#include <string>

#include "constants.hpp"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {
struct Query {
  /*** Make queries helpers ***/

  /* Insert query for movies */
  static auto make_insert_query(const Movies &movie) {
    return fmt::format(Query::insert_movie, movie.name(), movie.rating(),
                       movie.stat());
  }

  /* Insert query for tv shows */
  static auto make_insert_query(const TvShow &tvshow) {
    return fmt::format(Query::insert_tvshow, tvshow.name(), tvshow.rating(),
                       tvshow.stat(), tvshow.episode(), tvshow.last_episode());
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
    }
    return std::string("");
  }

  /*** INSERT QUERIES ***/

  /* INSERT tvshow */
  inline static std::string insert_tvshow =
    "INSERT INTO tvshow (name, rating, stats, episode, last_episode) "
    "VALUES "
    "('{0}', {1}, {2}, {3}, {4})";

  /* INSERT movies */
  inline static std::string insert_movie =
    "INSERT INTO movies (name, rating, stats) VALUES ('{0}', {1}, {2})";

  /*** SELECT QUERIES ***/

  /* SELECT * from movies */
  static constexpr auto select_all_movie = "SELECT * from movies";

  /* SELECT * from tvshow */
  static constexpr auto select_all_tvshow = "SELECT * from tvshow";

  /* SELECT * from movies using stats */
  inline static std::string select_movie_by_stats =
    "SELECT * from movies WHERE stats={}";

  /* SELECT * from tvshow using stats */
  inline static std::string select_tvshow_by_stats =
    "SELECT * from tvshow WHERE stats={}";

  /*** UPDATE QUERIES ***/

  /* UPDATE name */
  inline static std::string update_name =
    "UPDATE {} SET name='{}' WHERE id_{}={}";

  /* UPDATE stat */
  inline static std::string update_stat =
    "UPDATE {} SET stats={} WHERE id_{}={}";

  /* UPDATE rating */
  inline static std::string update_rating =
    "UPDATE {} SET rating={} WHERE id_{}={}";

  /* UPDATE total episode */
  inline static std::string update_total_episode =
    "UPDATE {} SET last_episode{} WHERE id_{}={}";

  /* UPDATE episode */
  inline static std::string update_episode =
    "UPDATE {} SET episode=episode + {} WHERE id_{}={}";

  /*** CREATE TABLE QUERIES ***/

  /* CREATE TABLE tvshow */
  inline static std::string create_table_tvshow =
    "CREATE TABLE IF NOT EXISTS {} (`id_tvshow` INTEGER PRIMARY KEY "
    "AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER, `episode`, `last_episode` "
    "INTEGER);";

  /* CREATE TABLE movies */
  inline static std::string create_table_movie =
    "CREATE TABLE IF NOT EXISTS {} (`id_movie` INTEGER PRIMARY KEY "
    "AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER);";
};
}  // namespace Pholos
