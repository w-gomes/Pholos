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
void Utility::usage()
{
    const std::string logo = fmt::format("\n\t:::::::::::::::::"
                                         "\n\t::::::::::::::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t::::::::::::::::::"
                                         "\n\t:::::::::::::::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::\n\n");

    const std::string commands = fmt::format("- Usage:\n"
                                             "\tOperations can have argument or not:\n"
                                             "\t1. <operations>\n\n"
                                             "\t2. <operations> <arg>\n\n"
                                             "\t-Operations:\n\n"
                                             "\t <-h or --help>\n"
                                             "\t <-x or --exit>\n"
                                             "\t <-c or --create>\n\n\n"
                                             "\t <-a or --add> <arg>\n"
                                             "\t <-e or --edit> <arg>\n"
                                             "\t <-d or --delete> <arg>\n"
                                             "\t <-s or --search> <arg>\n"
                                             "\t <-q or --query> <arg>\n");

    fmt::print("\n\tWelcome to Pholos!\n");
    fmt::print(logo);
    fmt::print(commands);
    fmt::print("\n\nDo you wish to proceed?(yes|no) ");
}

void Utility::run()
{
}

void Utility::help()
{
}

Utility *getUtility()
{
    assert(Utility::instance != nullptr);

    return Utility::instance;
}
}  // namespace Pholos
