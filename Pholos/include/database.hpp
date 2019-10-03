#pragma once

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
    void init();

  private:
    void create_table();
    void create_movie_table();
    void create_tvshow_table();
    void create_season_table();

  private:
    std::string database_name_ = "data.db";

    const std::vector<std::string> table_names_ = { "movies", "tvshow", "season" };
};

Database *get_database();
}  // namespace Pholos
