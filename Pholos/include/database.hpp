#pragma once

#include <array>
#include <map>
#include <optional>
#include <string>
#include <vector>

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

  void save(const Movies &movie);
  void save(const TvShow &show);
  bool is_in_database(const std::string &name, const char flag) const;
  std::vector<Movies> select_all_movies();
  std::vector<TvShow> select_all_tvshows();

 private:
  // Helper functions to create the database's tables.
  void create_table();
  void create_movie_table();
  void create_tvshow_table();

 private:
  std::string database_name_{"data.sqlite3"};

  static constexpr std::array table_names_{"movies", "tvshow"};
};

Database *get_database();
}  // namespace Pholos
