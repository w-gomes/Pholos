#include "database.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include "fmt/core.h"
#include "movies.hpp"
#include "tv-show.hpp"

#include <cassert>
#include <cctype>  // std::tolower()
#include <functional>
#include <iostream>
#include <map>

namespace Pholos {
Database *Database::instance = nullptr;

Database::Database()
{
  this->instance = this;
}

void Database::init(bool &loaded)
{
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

void Database::save(Movies &movie)
{
  std::string name  = movie.get_name();
  double rating     = movie.get_rating();
  int year          = movie.get_year();
  std::string stats = movie.get_stats();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query =
    fmt::format("INSERT INTO movies (name, rating, year, stats) VALUES ('{0}', {1}, {2}, '{3}')",
                name, rating, year, stats);
  db.exec(save_query);
  transaction.commit();
}

void Database::save(TvShow &show)
{
  std::string name          = show.get_name();
  double rating             = show.get_rating();
  int year                  = show.get_year();
  std::string stats         = show.get_stats();
  std::map<int, int> season = show.get_seasons();

  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string save_query =
    fmt::format("INSERT INTO tvshow (name, rating, year, stats) VALUES ('{0}', {1}, {2}, '{3}')",
                name, rating, year, stats);
  db.exec(save_query);

  const std::string query = fmt::format("SELECT id_tvshow FROM tvshow WHERE name = '{}'", name);

  int id = db.execAndGet(query);

  // s = season, epi = episode
  for (const auto &[s, epi] : season) {
    std::string save_query2 = fmt::format(
      "INSERT INTO season (id_season, nepisodes, tvshow_id) VALUES ({0}, {1}, {2})", s, epi, id);

    db.exec(save_query2);
  }

  transaction.commit();
}

bool Database::search(const std::string &name, const char flag) const
{
  const std::string query_type = [&] {
    if (std::tolower(flag) == 'm') {
      return "movies";
    } else if (std::tolower(flag) == 't') {
      return "tvshow";
    } else {
      return "";
    }
  }();
  assert(query_type != "");

  try {
    SQLite::Database db(this->database_name_);

    const std::string query = fmt::format("SELECT name FROM {} WHERE name='{}'", query_type, name);
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

void Database::delete_element(const std::string &name, const char flag) const
{
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE);
  SQLite::Transaction transaction(db);

  const std::string query_type = [&] {
    if (std::tolower(flag) == 'm') {
      return "movies";
    } else if (std::tolower(flag) == 't') {
      return "tvshow";
    } else {
      return "";
    }
  }();
  assert(query_type != "");

  const std::string query = fmt::format("DELETE FROM {} WHERE name='{}'", query_type, name);
  db.exec(query);

  transaction.commit();
}

void Database::create_table()
{
  fmt::print("Creating tables now...\n");
  this->create_movie_table();
  this->create_tvshow_table();
  this->create_season_table();
  fmt::print("Done\n");
}

void Database::create_movie_table()
{
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string movie_query =
    fmt::format("CREATE TABLE IF NOT EXISTS {} (`id_movie` INTEGER NOT NULL "
                "PRIMARY KEY AUTOINCREMENT, `name` TEXT "
                "NOT "
                "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT);",
                this->table_names_[0]);
  db.exec(movie_query);
  transaction.commit();
}

void Database::create_tvshow_table()
{
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string tv_query =
    fmt::format("CREATE TABLE IF NOT EXISTS {} (`id_tvshow` INTEGER NOT NULL PRIMARY "
                "KEY AUTOINCREMENT, `name` TEXT "
                "NOT "
                "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT);",
                this->table_names_[1]);
  db.exec(tv_query);
  transaction.commit();
}

void Database::create_season_table()
{
  SQLite::Database db(this->database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  SQLite::Transaction transaction(db);

  const std::string season =
    fmt::format("CREATE TABLE {} (`id_season` INTEGER NOT NULL, `nepisodes` INTEGER NOT NULL, "
                "`tvshow_id` INTEGER NOT NULL, PRIMARY KEY(`id_season`), FOREIGN KEY (tvshow_id) "
                "REFERENCES tvshow(id_tvshow));",
                this->table_names_[2]);
  db.exec(season);
  transaction.commit();
}

// is this really necessary?
Database *get_database()
{
  assert(Database::instance != nullptr);
  return Database::instance;
}
}  // namespace Pholos
