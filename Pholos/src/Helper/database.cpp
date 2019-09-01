#include "database.hpp"

#include <cassert>
#include <exception>
#include <iostream>

namespace Pholos {
Database *Database::instance = nullptr;

Database::Database()
{
    this->instance = this;
}

void Database::init()
{
    try {
        db_.connect("data.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Database::testing()
{
    try {
        sqlite3pp::database db("test.db");

        {
            db.execute("INSERT INTO contacts (name, phone) VALUES ('AAAA', '1234')");
        }

        {
            sqlite3pp::transaction xct(db);

            sqlite3pp::command cmd(db,
                                   "INSERT INTO contacts (name, phone) VALUES (?, ?)");

            std::cout << cmd.bind(1, "BBBB", sqlite3pp::copy) << std::endl;
            std::cout << cmd.bind(2, "1234", sqlite3pp::copy) << std::endl;
            std::cout << cmd.execute() << std::endl;

            std::cout << cmd.reset() << std::endl;

            cmd.binder() << "CCCC"
                         << "1234";

            std::cout << cmd.execute() << std::endl;

            xct.commit();
        }

        {
            sqlite3pp::transaction xct(db, true);
            sqlite3pp::command cmd(
                db, "INSERT INTO contacts (name, phone) VALUES (:name, :name)");

            std::cout << cmd.bind(":name", "DDDD", sqlite3pp::copy) << std::endl;

            std::cout << cmd.execute() << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Dude?" << std::endl;
    }
}

// is this really necessary?
Database *getDatabase()
{
    assert(Database::instance != nullptr);
    return Database::instance;
}
}  // namespace Pholos
