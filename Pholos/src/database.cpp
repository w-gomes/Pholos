#include "database.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include <cassert>  // assert()
#include <cctype>   // std::tolower()
#include <fstream>
#include <map>
#include <string>
#include <utility>  // std::move

#include "constants.hpp"
#include "fmt/format.h"
#include "movies.hpp"
#include "queries.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace internal {
inline auto type_to_string(Type type) -> std::string {
  switch (type) {
    case Type::Movie:
      return "movies";
    case Type::TvShow:
      return "tvshow";
    case Type::None:
      break;
  }
  return "";
}

// Check the select type: All or Filter
// In case it's filter type, checks for filter type.
// For now, we are using the Stats enum.
// const inline std::string what_select_type(Select_Type select_type, Stats
// stat) {
// }
}  // namespace internal

auto Database::create_database_file() -> bool {
  // Check if the database file already exists.
  std::ifstream file(Database::database_name_);
  if (file.is_open()) {
    // It does...
    fmt::print("Database file found!\n");
    return true;
  }

  // Database file doesn't exist, so we create an empty one.
  std::ofstream database_file(Database::database_name_);
  if (database_file.is_open()) {
    fmt::print("Database file {} doesn't exist. Creating one...\n",
               Database::database_name_);
    return true;
  }

  // Something wrong happened.
  return false;
}

auto Database::init(bool &loaded) -> void {
  bool database_exist = Database::create_database_file();
  if (!database_exist) {
    fmt::print(
      "An error occurred trying to read the database file. The file might not "
      "exist and couldn't create a new one.\n");
    loaded = false;
    return;
  }

  try {
    SQLite::Database db(Database::database_name_);
    fmt::print(
      "Database file {} opened successfully.\nChecking database tables...\n",
      Database::database_name_);
    bool table_exists = true;
    for (const auto &t : Database::table_names_) {
      table_exists = db.tableExists(t);
      if (!table_exists) {
        fmt::print("No tables found.\n");
        break;
      }
    }

    if (!table_exists) { Database::create_table(); }

    loaded = true;
  } catch (std::exception &e) {
    fmt::print("{}\n", e.what());
    loaded = false;
  }
}

// INSERT query.
// The client should pass the formatted query.
auto Database::insert(const std::string &query) -> void {
  SQLite::Database db(Database::database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  db.exec(query);
  transaction.commit();
}

// SELECT query.
/*
 * We want this method to work for both Movie and TvShow context.
 * So, the callee pass in the desired query:
 * - All or By Status.
 *   The Status can be the ones defined in constants.hpp as enum Stats.
 *
 *   So the type of query will be provided according to the desired query.
auto Database::select(Type context_type, Stats stat) {
  switch (context_type) {
    case Type::Movie:
      return this->select_movies(stat);
    case Type::TvShow:
      return this->select_tvshows(stat);
  }
}
*/

auto Database::select_movies(Stats st) -> std::map<int, Movies> {
  try {
    SQLite::Database db(Database::database_name_);
#if defined(_DEBUG)
    fmt::print("Database {} opened successfully.\n", db.getFilename().c_str());
#endif
    const auto query_str = [st]() -> std::string {
      switch (st) {
        case Stats::NotSet:
          return Query::select_all_movie;
        case Stats::Watching:
          return fmt::format(Query::select_movie_by_stats, 1);
        case Stats::PlanToWatch:
          return fmt::format(Query::select_movie_by_stats, 2);
        case Stats::Completed:
          return fmt::format(Query::select_movie_by_stats, 3);
        case Stats::Dropped:
          return fmt::format(Query::select_movie_by_stats, 4);
      }
      return std::string("");
    }();
    SQLite::Statement query(db, query_str);
#if defined(_DEBUG)
    fmt::print("SQLite statement {} compiled. Column counts {}\n",
               query.getQuery().c_str(),
               query.getColumnCount());
#endif
    std::map<int, Movies> movies_list;
    while (query.executeStep()) {
      const auto id          = query.getColumn(0);
      const std::string name = query.getColumn(1);
      const double rating    = query.getColumn(2);
      const int stat         = query.getColumn(3);

      auto movie = Movies(name, rating, stat);
      movies_list.try_emplace(id, movie);
    }
    return movies_list;
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
    return std::map<int, Movies>{};
  }
}

auto Database::select_tvshows(Stats st) -> std::map<int, TvShow> {
  try {
    SQLite::Database db(Database::database_name_);
#if defined(_DEBUG)
    fmt::print("Database {} opened successfully.\n", db.getFilename().c_str());
#endif
    const auto query_str = [st]() -> std::string {
      switch (st) {
        case Stats::NotSet:
          return Query::select_all_tvshow;
        case Stats::Watching:
          return fmt::format(Query::select_tvshow_by_stats, 1);
        case Stats::PlanToWatch:
          return fmt::format(Query::select_tvshow_by_stats, 2);
        case Stats::Completed:
          return fmt::format(Query::select_tvshow_by_stats, 3);
        case Stats::Dropped:
          return fmt::format(Query::select_tvshow_by_stats, 4);
      }
      return std::string("");
    }();
    SQLite::Statement query(db, query_str);
#if defined(_DEBUG)
    fmt::print("SQLite statement {} compiled. Column counts {}\n",
               query.getQuery().c_str(),
               query.getColumnCount());
#endif
    std::map<int, TvShow> tvshow_list;
    while (query.executeStep()) {
      const auto id          = query.getColumn(0);
      const std::string name = query.getColumn(1);
      const double rating    = query.getColumn(2);
      const int stat         = query.getColumn(3);
      const int episode      = query.getColumn(4);
      const int last_episode = query.getColumn(5);

      auto tvshow = TvShow(name, rating, stat, episode, last_episode);
      tvshow_list.try_emplace(id, tvshow);
    }
    return tvshow_list;
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
    return std::map<int, TvShow>{};
  }
}

// UPDATE queries
auto Database::update_name(const int id, const std::string &name, Type obj_type)
  -> void {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(!query_type.empty());

  // Maybe implement a generic function
  const std::string query =
    fmt::format(Query::update_name,
                query_type,
                name,
                (obj_type == Type::TvShow ? "tvshow" : "movie"),
                id);
  Database::execute_update(query);
}

auto Database::update_stat(const int id, const int stat, Type obj_type)
  -> void {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(!query_type.empty());

  const std::string query =
    fmt::format(Query::update_stat,
                query_type,
                stat,
                (obj_type == Type::TvShow ? "tvshow" : "movie"),
                id);
  Database::execute_update(query);
}

auto Database::update_rating(const int id, const double rating, Type obj_type)
  -> void {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(!query_type.empty());

  const std::string query =
    fmt::format(Query::update_rating,
                query_type,
                rating,
                (obj_type == Type::TvShow ? "tvshow" : "movie"),
                id);
  Database::execute_update(query);
}

auto Database::update_total_episode(const int id,
                                    const int total_episode,
                                    Type obj_type) -> void {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(!query_type.empty());

  const std::string query =
    fmt::format(Query::update_total_episode,
                query_type,
                total_episode,
                (obj_type == Type::TvShow ? "tvshow" : "movie"),
                id);
  Database::execute_update(query);
}

auto Database::update_episode(const int id, Type obj_type, const int distance)
  -> void {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(!query_type.empty());

  const std::string query =
    fmt::format(Query::update_episode,
                query_type,
                distance,
                (obj_type == Type::TvShow ? "tvshow" : "movie"),
                id);
  Database::execute_update(query);
}

// Private section
auto Database::execute_update(const std::string &query) -> void {
  try {
    SQLite::Database db(Database::database_name_, SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);

    db.exec(query);
    transaction.commit();
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
  }
}

auto Database::create_table() -> void {
  fmt::print("Creating tables now...\n");
  Database::create_movie_table();
  Database::create_tvshow_table();
  fmt::print("Done\n");
}

auto Database::create_movie_table() -> void {
  SQLite::Database db(Database::database_name_,
                      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  db.exec(Query::make_create_table_query(Type::Movie));
  transaction.commit();
}

auto Database::create_tvshow_table() -> void {
  SQLite::Database db(Database::database_name_,
                      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  db.exec(Query::make_create_table_query(Type::TvShow));
  transaction.commit();
}
}  // namespace Pholos
