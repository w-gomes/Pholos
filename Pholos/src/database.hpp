#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>

#include "constants.hpp"

namespace Pholos {

class Movies;
class TvShow;

// - Database API
// All the database calls are provided by this module
class Database {
 public:
  Database() = default;

  // No copy or move allowed
  Database(const Database &obj) = delete;
  Database &operator=(const Database &obj) = delete;
  Database(Database &&obj)                 = delete;
  Database &operator=(Database &&obj) = delete;

  ~Database() = default;

  // This is called after creating the Database object.
  // It checks if the database file exits, if not, it creates one.
  // Then it creates the database tables.
  // it calls create_database_file()
  void init(bool &loaded);

  static void change_database_name(std::string database_name) {
    Database::database_name_ = (std::move(database_name));
  }
  static std::string name() { return Database::database_name_; }

  // INSERT queries
  static void insert(std::string query);

  // SELECT queries
  // For multiple objects we return a map,
  // std::map<int, Object>,
  // and for a single object we return a pair
  // std::pair<int, Object>.
  // id | object
  // auto select(Type context_type, Stats stat = Stats::NotSet);

  // TODO: Make these two private.
  static std::map<int, Movies> select_movies(Stats st = Stats::NotSet);
  static std::map<int, TvShow> select_tvshows(Stats st = Stats::NotSet);
  // std::pair<int, Movies> select_movies();
  // std::pair<int, TvShow> select_tvshows();
  // TODO: select * FROM (movies|tvshow) WHERE stats=#;
  // So, we can print a single object.

  // UPDATE queries
  static void update_name(const int id, const std::string &name, Type obj_type);
  static void update_stat(const int id, const int stat, Type obj_type);
  static void update_rating(const int id, const double rating, Type obj_type);
  static void update_total_episode(const int id, const int total_episode,
                                   Type obj_type);
  static void update_episode(const int id, Type obj_type,
                             const int distance = 1);

  // Private section
 private:
  static bool create_database_file();

  // Helper functions to create the database's tables.
  static void execute_update(const std::string &query);
  static void create_table();
  static void create_movie_table();
  static void create_tvshow_table();

 private:
  inline static std::string database_name_{"data.sqlite3"};

  static constexpr std::array table_names_{"tvshow", "movies"};
};
}  // namespace Pholos
