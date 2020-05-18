#include "database.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include <cassert>  // assert()
#include <cctype>   // std::tolower()
#include <iostream>
#include <map>
#include <string>

#include "fmt/core.h"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace internal {
const inline std::string what_type(const char flag) {
  if (std::tolower(flag) == 'm') {
    return "movies";
  } else if (std::tolower(flag) == 't') {
    return "tvshow";
  } else {
    return "";
  }
}
}  // namespace internal

Database::Database() { this->instance = this; }

void Database::init(bool &loaded) {
  try {
    SQLite::Database db(this->database_name_);
    fmt::print("Database file {} opened successfully.\nChecking database tables...\n",
               this->database_name_);
    bool table_exists = true;
    for (const auto &t : this->table_names_) {
      table_exists = db.tableExists(t);
      if (!table_exists) {
        fmt::print("Some tables are missing...\n");
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

void Database::save(const Movies &movie) {
  std::string name = movie.name();
  double rating    = movie.rating();
  int stat         = movie.stat();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query = fmt::format(
    "INSERT INTO movies (name, rating, stats) VALUES ('{0}', {1}, {2})", name, rating, stat);
  db.exec(save_query);
  transaction.commit();
}

void Database::save(const TvShow &show) {
  std::string name = show.name();
  double rating    = show.rating();
  int stat         = show.stat();
  int episode      = show.episode();
  int last_episode = show.last_episode();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query = fmt::format(
    "INSERT INTO tvshow (name, rating, stats, episode, last_episode) VALUES ('{0}', {1}, {2}, {3}, "
    "{4})",
    name, rating, stat, episode, last_episode);

  db.exec(save_query);
  transaction.commit();
}

std::map<int, Movies> Database::select_all_movies() {
  try {
    SQLite::Database db(this->database_name_);
#if defined(_DEBUG)
    fmt::print("Database {} opened successfully.\n", db.getFilename().c_str());
#endif
    SQLite::Statement query(db, "SELECT * from movies");
#if defined(_DEBUG)
    fmt::print("SQLite statement {} compiled. Column counts {}\n", query.getQuery().c_str(),
               query.getColumnCount());
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

std::map<int, TvShow> Database::select_all_tvshows() {
  try {
    SQLite::Database db(this->database_name_);
#if defined(_DEBUG)
    fmt::print("Database {} opened successfully.\n", db.getFilename().c_str());
#endif
    SQLite::Statement query(db, "SELECT * from tvshow");
#if defined(_DEBUG)
    fmt::print("SQLite statement {} compiled. Column counts {}\n", query.getQuery().c_str(),
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
void Database::update_name(const int id, const std::string &name, const char obj_type) {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  // Maybe implement a generic function
  const std::string query = fmt::format("UPDATE {} SET name='{}' WHERE id_{}={}", query_type, name,
                                        (obj_type == 't' ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_stat(const int id, const int stat, const char obj_type) {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  const std::string query = fmt::format("UPDATE {} SET stats={} WHERE id_{}={}", query_type, stat,
                                        (obj_type == 't' ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_rating(const int id, const double rating, const char obj_type) {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  const std::string query = fmt::format("UPDATE {} SET rating={} WHERE id_{}={}", query_type,
                                        rating, (obj_type == 't' ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_total_episode(const int id, const int total_episode, const char obj_type) {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  const std::string query = fmt::format("UPDATE {} SET last_episode={} WHERE id_{}={}", query_type,
                                        total_episode, (obj_type == 't' ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

void Database::update_episode(const int id, const char obj_type, const int distance) {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  const std::string query =
    fmt::format("UPDATE {} SET episode=episode + {} WHERE id_{}={}", query_type, distance,
                (obj_type == 't' ? "tvshow" : "movie"), id);
  this->execute_update(query);
}

bool Database::is_in_database(const std::string &name, const char obj_type) const {
  const std::string query_type = internal::what_type(obj_type);
  assert(query_type != "");

  try {
    SQLite::Database db(this->database_name_);

    const std::string query =
      fmt::format("SELECT alias FROM {} WHERE alias='{}'", query_type, name);
    const std::string value = db.execAndGet(query);

    if (value.size() == 0) {
      return false;
    }

    return true;
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
    return false;
  }
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
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string movie_query = fmt::format(
    "CREATE TABLE IF NOT EXISTS {} (`id_movie` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER);",
    this->table_names_[0]);

  db.exec(movie_query);
  transaction.commit();
}

void Database::create_tvshow_table() {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string tv_query = fmt::format(
    "CREATE TABLE IF NOT EXISTS {} (`id_tvshow` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT NOT "
    "NULL, `rating` REAL, `stats` INTEGER, `episode`, `last_episode` INTEGER);",
    this->table_names_[1]);
  db.exec(tv_query);
  transaction.commit();
}

// is this really necessary?
Database *get_database() {
  assert(Database::instance != nullptr);
  return Database::instance;
}
}  // namespace Pholos
