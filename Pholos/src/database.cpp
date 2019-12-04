#include "database.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include <cassert>
#include <cctype>  // std::tolower()
#include <functional>
#include <iostream>
#include <map>
#include <tuple>

#include "fmt/core.h"
#include "movies.hpp"
#include "tv-show.hpp"

namespace Pholos {

namespace Detail {
const inline std::string what_type(const char flag) {
  if (std::tolower(flag) == 'm') {
    return "movies";
  } else if (std::tolower(flag) == 't') {
    return "tvshow";
  } else {
    return "";
  }
}
}  // namespace Detail

Database *Database::instance = nullptr;

Database::Database() { this->instance = this; }

void Database::init(bool &loaded) {
  try {
    SQLite::Database db(this->database_name_);
    fmt::print("Database file {} opened successfully.\nChecking database tables...\n", "data.db");
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

void Database::save(Movies &movie) {
  std::string name  = movie.get_name();
  double rating     = movie.get_rating();
  int year          = movie.get_year();
  std::string stats = movie.get_stats();
  std::string alias = movie.get_alias();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query = fmt::format(
    "INSERT INTO movies (name, rating, year, stats, alias) VALUES ('{0}', {1}, {2}, '{3}', '{4}')",
    name, rating, year, stats, alias);
  db.exec(save_query);
  transaction.commit();
}

void Database::save(TvShow &show) {
  std::string name          = show.get_name();
  double rating             = show.get_rating();
  int year                  = show.get_year();
  std::string stats         = show.get_stats();
  std::map<int, int> season = show.get_seasons();
  std::string alias         = show.get_alias();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query = fmt::format(
    "INSERT INTO tvshow (name, rating, year, stats, alias) VALUES ('{0}', {1}, {2}, '{3}', '{4}')",
    name, rating, year, stats, alias);
  db.exec(save_query);
  transaction.commit();

  if (season.empty()) {
    return;
  }

  this->add_season(alias, season);
}

void Database::add_season(const std::string &name, const std::map<int, int> &season) {
  int id = this->get_element_id(name, 't');

  if (id == -1) {
    fmt::print("Element not found\n");
    return;
  }

  try {
    SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
    SQLite::Transaction transaction(db);

    // s = season, epi = episode
    for (const auto &[s, epi] : season) {
      std::string save_query = fmt::format(
        "INSERT INTO season (id_season, nepisodes, tvshow_id) VALUES ({0}, {1}, {2})", s, epi, id);
      db.exec(save_query);
    }

    transaction.commit();
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
  }
}

int Database::get_element_id(const std::string &name, const char flag) const {
  const std::tuple<std::string, std::string> query_type = [&] {
    if (std::tolower(flag) == 'm') {
      return std::make_tuple(std::string("movies"), std::string("id_movie"));
    } else if (std::tolower(flag) == 't') {
      return std::make_tuple(std::string("tvshow"), std::string("id_tvshow"));
    } else {
      return std::make_tuple(std::string(""), std::string(""));
    }
  }();
  assert(std::get<0>(query_type) != "");

  int id;
  try {
    SQLite::Database db(this->database_name_);

    const std::string query = fmt::format("SELECT {} FROM {} WHERE alias='{}'",
                                          std::get<1>(query_type), std::get<0>(query_type), name);

    id = db.execAndGet(query);
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
    id = -1;
  }

  return id;
}

bool Database::is_in_database(const std::string &name, const char flag) const {
  const std::string query_type = Detail::what_type(flag);
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

void Database::delete_element(const std::string &name, const char flag) const {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string query_type = Detail::what_type(flag);
  assert(query_type != "");

  if (std::tolower(flag) == 't') {
    int id = this->get_element_id(name, 't');

    const std::string query_season = fmt::format("DELETE FROM season WHERE tvshow_id='{}'", id);
    db.exec(query_season);
  }

  const std::string query = fmt::format("DELETE FROM {} WHERE alias='{}'", query_type, name);
  db.exec(query);

  transaction.commit();
}

void Database::create_table() {
  fmt::print("Creating tables now...\n");
  this->create_movie_table();
  this->create_tvshow_table();
  this->create_season_table();
  fmt::print("Done\n");
}

void Database::create_movie_table() {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string movie_query = fmt::format(
    "CREATE TABLE IF NOT EXISTS {} (`id_movie` INTEGER NOT NULL "
    "PRIMARY KEY AUTOINCREMENT, `name` TEXT "
    "NOT "
    "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT, `alias` TEXT);",
    this->table_names_[0]);
  db.exec(movie_query);
  transaction.commit();
}

void Database::create_tvshow_table() {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string tv_query = fmt::format(
    "CREATE TABLE IF NOT EXISTS {} (`id_tvshow` INTEGER NOT NULL PRIMARY "
    "KEY AUTOINCREMENT, `name` TEXT "
    "NOT "
    "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT, `alias` TEXT);",
    this->table_names_[1]);
  db.exec(tv_query);
  transaction.commit();
}

void Database::create_season_table() {
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string season = fmt::format(
    "CREATE TABLE {} (`id_season` INTEGER NOT NULL, `nepisodes` INTEGER NOT NULL, "
    "`tvshow_id` INTEGER NOT NULL, FOREIGN KEY (tvshow_id) "
    "REFERENCES tvshow(id_tvshow));",
    this->table_names_[2]);
  db.exec(season);
  transaction.commit();
}

void Database::list_all_movies(std::vector<std::string> &message_vector) {
  try {
    SQLite::Database db(this->database_name_);
    fmt::print("Database {} opened successfully.\n", db.getFilename().c_str());

#if defined(_DEBUG)
    SQLite::Statement query(db, "SELECT * from movies");
    fmt::print("SQLite statement {} compiled. Column counts {}\n", query.getQuery().c_str(),
               query.getColumnCount());
#endif

    while (query.executeStep()) {
      const int id            = query.getColumn(0);
      const std::string name  = query.getColumn(1);
      const double rating     = query.getColumn(2);
      const int year          = query.getColumn(3);
      const std::string stats = query.getColumn(4);
      const std::string alias = query.getColumn(5);

      auto fmt = fmt::format(
        "ID: {0} - Name: {1} - Rating: {2} - Year: {3} - "
        "Stats: {4} - Alias: {5}\n",
        id, name, rating, year, stats, alias);
      message_vector.push_back(fmt);
    }
  } catch (std::exception &e) {
#if defined(_DEBUG)
    fmt::print("{}\n", e.what());
#endif
  }
}

// is this really necessary?
Database *get_database() {
  assert(Database::instance != nullptr);
  return Database::instance;
}
}  // namespace Pholos
