#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>

namespace Pholos {

class Movies;
class TvShow;

// - Database API
// All the database calls are provided by this module
class Database {
 public:
  // There should be only one object of Database type.
  inline static Database *instance = nullptr;
  Database();

  // No copy or move allowed
  Database(const Database &obj) = delete;
  Database &operator=(const Database &obj) = delete;
  Database(Database &&obj)                 = delete;
  Database &operator=(Database &&obj) = delete;

  ~Database() = default;

  // This is called after the creation of Database object to check
  // if a database file (i.e. data.db) exists. Otherwise, application exits.
  //
  // TODO: If data.db doesn't exist, the application should create a new data.db file
  // and create its needed tables.
  void init(bool &loaded);

  bool is_in_database(const std::string &name, const char obj_type) const;

  // INSERT queries
  void save(const Movies &movie);
  void save(const TvShow &show);

  // SELECT queries
  std::map<int, Movies> select_all_movies();
  std::map<int, TvShow> select_all_tvshows();
  // TODO: select * FROM (movies|tvshow) WHERE ID=#;
  // So, we can print a single object.

  // UPDATE queries
  void update_name(int id, const std::string &name, const char obj_type);
  void update_stat(int id, int stat, const char obj_type);
  void update_rating(int id, double rating, const char obj_type);
  void update_total_episode(int id, int total_episode, const char obj_type);
  void update_episode(int id, const char obj_type, int distance = 1);

 private:
  // Helper functions to create the database's tables.
  void execute_update(const std::string &query);
  void create_table();
  void create_movie_table();
  void create_tvshow_table();

 private:
  std::string database_name_{"data.sqlite3"};

  static constexpr std::array table_names_{"movies", "tvshow"};
};

Database *get_database();
}  // namespace Pholos
