#pragma once

#include <array>
#include <filesystem>
#include <map>
#include <optional>
#include <string>

#include "constants.hpp"

namespace Pholos {

namespace fs = std::filesystem;

struct Movies;
struct TvShow;

// - Database API
// All the database calls are provided by this module
class Database {
 public:
  explicit Database(fs::path const &path)
    : root_path_(path) {}

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
  auto insert(const std::string &query) -> void;

  // SELECT queries
  // For multiple objects we return a map,
  // std::map<int, Object>,
  // and for a single object we return a pair
  // std::pair<int, Object>.
  // id | object
  // auto select(Type context_type, Stats stat = Stats::NotSet);

  // TODO: Make these two private.
  auto select_movies(Stats st = Stats::NotSet) -> std::map<int, Movies>;
  auto select_tvshows(Stats st = Stats::NotSet) -> std::map<int, TvShow>;
  // std::pair<int, Movies> select_movies();
  // std::pair<int, TvShow> select_tvshows();
  // TODO: select * FROM (movies|tvshow) WHERE stats=#;
  // So, we can print a single object.

  // UPDATE queries
  auto update_name(int id, const std::string &name, Type obj_type) -> void;
  auto update_stat(int id, int stat, Type obj_type) -> void;
  auto update_rating(int id, double rating, Type obj_type) -> void;
  auto update_total_episode(int id, int total_episode, Type obj_type) -> void;
  auto update_episode(int id, Type obj_type, int distance = 1) -> void;

  // Private section
 private:
  auto create_database_file() -> bool;

  // Helper functions to create the database's tables.
  auto execute_update(const std::string &query) -> void;
  auto create_table() -> void;
  auto create_movie_table() -> void;
  auto create_tvshow_table() -> void;

  [[nodiscard]] auto get_database_path() const -> std::string;

  inline static std::string database_name_{"data.sqlite3"};
  inline static std::string data_folder_{"data"};
  inline static std::string backup_folder_{"backup"};

  static constexpr std::array table_names_{"tvshow", "movies"};

  fs::path root_path_;
};
}  // namespace Pholos
