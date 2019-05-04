#include "Utility.hpp"
#include "fmt/fmt.hpp"

#include <cassert>

namespace Pholos {

Utility *Utility::instance = nullptr;

Utility::Utility()
{
    this->instance = this;
}

// This gets called whenever arguments aren't passed
// or -h passed as argument
void Utility::usage()
{
    auto logo = fmt::format("\n::::::::::::::::"
                            "\n:::::::::::::::::"
                            "\n::::        ::::::"
                            "\n::::        ::::::"
                            "\n::::        ::::::"
                            "\n:::::::::::::::::"
                            "\n::::::::::::::::"
                            "\n::::"
                            "\n::::"
                            "\n::::"
                            "\n::::"
                            "\n::::"
                            "\n::::\n\n");

    fmt::print(logo);
}

Utility *getUtility()
{
    assert(Utility::instance != nullptr);

    return Utility::instance;
}
}  // namespace Pholos
