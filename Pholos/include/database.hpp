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

  // This is called after creating the Database object.
  // It checks if the database file exits, if not, it creates one.
  // Then it creates the database tables.
  // it calls create_database_file()
  void init(bool &loaded);

  void set_database_name(std::string database_name) {
    this->database_name_ = (std::move(database_name));
  }
  std::string name() const { return this->database_name_; }

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
  void update_name(const int id, const std::string &name, const char obj_type);
  void update_stat(const int id, const int stat, const char obj_type);
  void update_rating(const int id, const double rating, const char obj_type);
  void update_total_episode(const int id, const int total_episode,
                            const char obj_type);
  void update_episode(const int id, const char obj_type,
                      const int distance = 1);

 private:
  bool create_database_file();

  // Helper functions to create the database's tables.
  void execute_update(const std::string &query);
  void create_table();
  void create_movie_table();
  void create_tvshow_table();

 private:
  std::string database_name_{};

  static constexpr std::array table_names_{"movies", "tvshow"};
};

Database *get_database();
}  // namespace Pholos
