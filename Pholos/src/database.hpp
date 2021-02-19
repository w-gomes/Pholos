#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>

#include "constants.hpp"

namespace Pholos {

struct Movies;
struct TvShow;

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
  auto init(bool &loaded) -> void;

  static auto change_database_name(std::string database_name) -> void {
    Database::database_name_ = (std::move(database_name));
  }
  static auto name() -> std::string { return Database::database_name_; }

  // INSERT queries
  static auto insert(const std::string &query) -> void;

  // SELECT queries
  // For multiple objects we return a map,
  // std::map<int, Object>,
  // and for a single object we return a pair
  // std::pair<int, Object>.
  // id | object
  // auto select(Type context_type, Stats stat = Stats::NotSet);

  // TODO: Make these two private.
  static auto select_movies(Stats st = Stats::NotSet) -> std::map<int, Movies>;
  static auto select_tvshows(Stats st = Stats::NotSet) -> std::map<int, TvShow>;
  // std::pair<int, Movies> select_movies();
  // std::pair<int, TvShow> select_tvshows();
  // TODO: select * FROM (movies|tvshow) WHERE stats=#;
  // So, we can print a single object.

  // UPDATE queries
  static auto update_name(const int id, const std::string &name, Type obj_type)
    -> void;
  static auto update_stat(const int id, const int stat, Type obj_type) -> void;
  static auto update_rating(const int id, const double rating, Type obj_type)
    -> void;
  static auto update_total_episode(const int id,
                                   const int total_episode,
                                   Type obj_type) -> void;
  static auto update_episode(const int id,
                             Type obj_type,
                             const int distance = 1) -> void;

  // Private section
 private:
  static auto create_database_file() -> bool;

  // Helper functions to create the database's tables.
  static auto execute_update(const std::string &query) -> void;
  static auto create_table() -> void;
  static auto create_movie_table() -> void;
  static auto create_tvshow_table() -> void;

  inline static std::string database_name_{"data.sqlite3"};

  static constexpr std::array table_names_{"tvshow", "movies"};
};
}  // namespace Pholos
