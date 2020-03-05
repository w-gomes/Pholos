#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace Pholos {

class Movies;
class TvShow;

class Database {
 public:
  static Database *instance;
  Database();

  Database(const Database &obj) = delete;
  Database &operator=(const Database &obj) = delete;
  Database(Database &&obj)                 = delete;
  Database &operator=(Database &&obj) = delete;

  ~Database() = default;

  void save(Movies &movie);
  void save(TvShow &show);
  bool is_in_database(const std::string &name, const char flag) const;
  void delete_element(const std::string &name, const char flag) const;
  std::vector<std::string> list_all_movies();
  void init(bool &loaded);

 private:
  void create_table();
  void create_movie_table();
  void create_tvshow_table();
  void create_season_table();

  unsigned long long get_element_id(const std::string &name, const char flag) const;
  void Database::add_season(const std::string &name, const std::map<int, int> &season);

 private:
  std::string database_name_ = "data.db";

  const std::vector<std::string> table_names_ = {"movies", "tvshow", "season"};
};

Database *get_database();
}  // namespace Pholos
