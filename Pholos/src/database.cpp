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
const inline std::string type_to_string(Type type) {
  switch (type) {
    case Type::Movie:
      return "movies";
    case Type::TvShow:
      return "tvshow";
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

bool Database::create_database_file() {
  // Check if the database file already exists.
  std::ifstream file(this->database_name_);
  if (file.is_open()) {
    // It does...
    fmt::print("Database file exists!\n");
    return true;
  }

  // Database file doesn't exist, so we create an empty one.
  std::ofstream database_file(this->database_name_);
  if (database_file.is_open()) {
    fmt::print("Database file {} doesn't exist. Creating one...\n",
               this->database_name_);
    return true;
  }

  // Something wrong happened.
  return false;
}

Database::Database() { this->instance = this; }

void Database::init(bool &loaded) {
  bool database_exist = this->create_database_file();
  if (!database_exist) {
    fmt::print(
      "An error occurred trying to read the database file. The file might not "
      "exist and couldn't create a new one.\n");
    loaded = false;
    return;
  }

  try {
    SQLite::Database db(this->database_name_);
    fmt::print(
      "Database file {} opened successfully.\nChecking database tables...\n",
      this->database_name_);
    bool table_exists = true;
    for (const auto &t : this->table_names_) {
      table_exists = db.tableExists(t);
      if (!table_exists) {
        fmt::print("No tables found.\n");
        break;
      }
    }

    if (!table_exists) {
      this->create_table();
    }

    loaded = true;
  } catch (std::exception &e) {
    fmt::print("{}\n", e.what());
    loaded = false;
  }
}

// INSERT query.
// The client should pass the formatted query.
void Database::insert(std::string query) {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  db.exec(std::move(query));
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

std::map<int, Movies> Database::select_movies(Stats st) {
  try {
    SQLite::Database db(this->database_name_);
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
               query.getQuery().c_str(), query.getColumnCount());
#endif
    std::map<int, Movies> movies_list;
    while (query.executeStep()) {
      const auto id          = query.getColumn(0);
      const std::string name = query.getColumn(1);
      const double rating    = query.getColumn(2);
      const int stat         = query.getColumn(3);

      Movies movie(name, rating, stat);
      movies_list[id] = movie;
    }
    return movies_list;
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
    return std::map<int, Movies>{};
  }
}

std::map<int, TvShow> Database::select_tvshows(Stats st) {
  try {
    SQLite::Database db(this->database_name_);
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
               query.getQuery().c_str(), query.getColumnCount());
#endif
    std::map<int, TvShow> tvshow_list;
    while (query.executeStep()) {
      const auto id          = query.getColumn(0);
      const std::string name = query.getColumn(1);
      const double rating    = query.getColumn(2);
      const int stat         = query.getColumn(3);
      const int episode      = query.getColumn(4);
      const int last_episode = query.getColumn(5);

      TvShow tvshow(name, stat, rating, episode, last_episode);
      tvshow_list[id] = tvshow;
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
void Database::update_name(const int id, const std::string &name,
                           Type obj_type) {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(query_type != "");

  // Maybe implement a generic function
  const std::string query =
    fmt::format(Query::update_name, query_type, name,
                (obj_type == Type::TvShow ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_stat(const int id, const int stat, Type obj_type) {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(query_type != "");

  const std::string query =
    fmt::format(Query::update_stat, query_type, stat,
                (obj_type == Type::TvShow ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_rating(const int id, const double rating, Type obj_type) {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(query_type != "");

  const std::string query =
    fmt::format(Query::update_rating, query_type, rating,
                (obj_type == Type::TvShow ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_total_episode(const int id, const int total_episode,
                                    Type obj_type) {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(query_type != "");

  const std::string query =
    fmt::format(Query::update_total_episode, query_type, total_episode,
                (obj_type == Type::TvShow ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_episode(const int id, Type obj_type, const int distance) {
  const std::string query_type = internal::type_to_string(obj_type);
  assert(query_type != "");

  const std::string query =
    fmt::format(Query::update_episode, query_type, distance,
                (obj_type == Type::TvShow ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

// Private section
void Database::execute_update(const std::string &query) {
  try {
    SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);

    db.exec(query);
    transaction.commit();
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
  }
}

void Database::create_table() {
  fmt::print("Creating tables now...\n");
  this->create_movie_table();
  this->create_tvshow_table();
  fmt::print("Done\n");
}

void Database::create_movie_table() {
  SQLite::Database db(this->database_name_,
                      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  db.exec(Query::make_create_table_query(Type::Movie));
  transaction.commit();
}

void Database::create_tvshow_table() {
  SQLite::Database db(this->database_name_,
                      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);
  db.exec(Query::make_create_table_query(Type::TvShow));
  transaction.commit();
}

// is this really necessary?
Database *get_database() {
  assert(Database::instance != nullptr);
  return Database::instance;
}
}  // namespace Pholos
