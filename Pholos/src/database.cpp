#include "database.hpp"

#include <SQLiteCpp/SQLiteCpp.h>

#include "fmt/core.h"
#include "movies.hpp"
#include "tv-show.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <map>

namespace Pholos {
Database *Database::instance = nullptr;

/* Handle exception thrown when data.db doesn't exist or can't find it. */
Database::Database()
{
    this->instance = this;
}

void Database::init()
{
    SQLite::Database db("data.db");
    fmt::print("Database file {} opened successfully.\nChecking database tables...\n",
               "data.db");
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
}

void Database::save(TvShow &show)
{
    std::string name          = show.get_name();
    double rating             = show.get_rating();
    int year                  = show.get_year();
    std::string stats         = show.get_stats();
    std::map<int, int> season = show.get_seasons();
}

void Database::save(Movies &movie)
{
    std::string name  = movie.get_name();
    double rating     = movie.get_rating();
    int year          = movie.get_year();
    std::string stats = movie.get_stats();
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
    SQLite::Database db("data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Transaction transaction(db);

    const std::string movie_query =
        fmt::format("CREATE TABLE IF NOT EXISTS \"movies\" (`id_movie` INTEGER NOT NULL "
                    "PRIMARY KEY AUTOINCREMENT, `name` TEXT "
                    "NOT "
                    "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT);");
    db.exec(movie_query);
    transaction.commit();
}

void Database::create_tvshow_table()
{
    SQLite::Database db("data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Transaction transaction(db);

    const std::string tv_query = fmt::format(
        "CREATE TABLE IF NOT EXISTS \"tvshow\" (`id_tvshow` INTEGER NOT NULL PRIMARY "
        "KEY AUTOINCREMENT, `name` TEXT "
        "NOT "
        "NULL, `rating` REAL, `year` INTEGER, `stats` TEXT);");
    db.exec(tv_query);
    transaction.commit();
}

void Database::create_season_table()
{
    SQLite::Database db("data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Transaction transaction(db);

    const std::string season = fmt::format(
        "CREATE TABLE `{}` (`id_season` INTEGER NOT NULL, `nepisodes` INTEGER NOT NULL, "
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
