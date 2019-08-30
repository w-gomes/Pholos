#include "database.hpp"

#include <cassert>

namespace Pholos {
Database *Database::instance = nullptr;

Database::Database()
{
    this->instance = this;
}

void Database::init()
{
}

// is this really necessary?
Database *getDatabase()
{
    assert(Database::instance != nullptr);
    return Database::instance;
}
}  // namespace Pholos
