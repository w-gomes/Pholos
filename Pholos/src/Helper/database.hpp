#pragma once

#include <exception>
#include <iostream>
#include <type_traits>

#include "sqlite3pp.h"

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
    void testing();

    template <class Content>
    void save(Content &content)
    {
        std::string name;
        double rating;
        int year;
        std::string stats;

        if (std::is_class<Movies>::value) {
            name   = content.getName();
            rating = content.getRating();
            year   = content.getYear();
            stats  = content.getStats();
            try {
                std::clog << "Saving to database" << std::endl;
                sqlite3pp::transaction xct(this->db_);

                sqlite3pp::command cmd(
                    this->db_,
                    "INSERT INTO movies (name, rating, year, stats) VALUES (?, ?, ?, ?)");
                cmd.binder() << name << rating << year << stats;
                cmd.execute();
                xct.commit();
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }

        } else if (std::is_class<TvShow>::value) {
        }
    }

  private:
    sqlite3pp::database db_;
};

Database *getDatabase();
}  // namespace Pholos
