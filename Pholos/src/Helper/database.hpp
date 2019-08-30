#pragma once

namespace Pholos {
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
};

Database *getDatabase();
}  // namespace Pholos
