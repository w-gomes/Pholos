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
// All the database access are provided by this module
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

  void save(Movies &movie);
  void save(TvShow &show);
  bool is_in_database(const std::string &name, const char flag) const;
  void delete_element(const std::string &name, const char flag) const;
  std::vector<std::string> list_all_movies();

 private:
  // Helper functions to create the database's tables.
  void create_table();
  void create_movie_table();
  void create_tvshow_table();
  void create_season_table();

  unsigned long long get_element_id(const std::string &name, const char flag) const;
  void Database::add_season(const std::string &name, const std::map<int, int> &season);

 private:
  std::string database_name_{"data.db"};

  std::array<const std::string, 3> table_names_{"movies", "tvshow", "season"};
};

Database *get_database();
}  // namespace Pholos
