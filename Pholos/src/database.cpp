#include "database.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <map>

#include "fmt/core.h"
#include "movies.hpp"
#include "sqlite3.h"
#include "tv-show.hpp"

namespace Pholos {
Database *Database::instance = nullptr;

Database::Database()
{
    this->instance = this;
}

void Database::init()
{
    int rc;

    std::clog << "init database...\n";
    rc = sqlite3_open("data.db", &this->db_);
    if (rc) {
        fmt::print("Can't open database: {}!", sqlite3_errmsg(this->db_));
    } else {
        fmt::print("Opened database succesfully!\n");
    }
}

void Database::close()
{
    sqlite3_close(this->db_);
}

void Database::save(TvShow &show)
{
    this->init();
    std::string name          = show.getName();
    double rating             = show.getRating();
    int year                  = show.getYear();
    std::string stats         = show.getStats();
    std::map<int, int> season = show.getSeasons();

    // database error
    char *zErrMsg = nullptr;

    std::string tempSqlShow = fmt::format(
        "INSERT INTO tvshow (name,rating,year,stats) VALUES ('{0}', {1}, {2}, '{3}');");
    const char *sqlInsertShow = tempSqlShow.c_str();

    int rc = sqlite3_exec(this->db_, sqlInsertShow, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fmt::print("SQL Error: {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Incomplete: No idea how to retrieve data from db with sqlite3 c++
    std::string tempSqlSeason =
        fmt::format("SELECT id FROM tvshow WHERE name = '{}';", name);
    const char *sqlSelectId = tempSqlSeason.c_str();

    rc = sqlite3_exec(this->db_, sqlSelectId, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fmt::print("SQL Error: {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    for (const auto &[key, value] : season) {
    }

    this->close();
}

void Database::save(Movies &movie)
{
    this->init();
    std::string name  = movie.getName();
    double rating     = movie.getRating();
    int year          = movie.getYear();
    std::string stats = movie.getStats();

    // database error
    char *zErrMsg = nullptr;

    std::string tempSql = fmt::format(
        "INSERT INTO movies (name,rating,year,stats) VALUES ('{0}', {1}, {2}, '{3}');",
        name, rating, year, stats);
    const char *sql = tempSql.c_str();

    int rc = sqlite3_exec(this->db_, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fmt::print("SQL Error: {}\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    this->close();
}

// is this really necessary?
Database *getDatabase()
{
    assert(Database::instance != nullptr);
    return Database::instance;
}
}  // namespace Pholos
