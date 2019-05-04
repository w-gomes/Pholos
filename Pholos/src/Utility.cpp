#include "Utility.hpp"
#include "fmt/fmt.hpp"

#include <cassert>

namespace Pholos {

Utility *Utility::instance = nullptr;

Utility::Utility()
{
    this->instance = this;
}

void Utility::usage()
{
    auto usage = fmt::format("test\n monkas\n");
    fmt::print(usage);
}

Utility *getUtility()
{
    assert(Utility::instance != nullptr);

    return Utility::instance;
}
}  // namespace Pholos
