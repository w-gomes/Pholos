#pragma once
#include <iostream>

#include "sqlite3.h"

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

    void init();
    void close();
    void save(Movies &movie);
    void save(TvShow &show);

  private:
    sqlite3 *db_;
};

Database *getDatabase();
}  // namespace Pholos
