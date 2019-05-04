#include "fmt/fmt.hpp"

#include "Controller.hpp"
#include "Utility.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

using namespace Pholos;

int main(int argc, char **argv)
{
    Controller control;
    std::vector<std::string> args;
    Utility utility;
    if (argc > 1) {
        std::transform(argv + 1, argv + argc, std::back_inserter(args), [&](auto s) { return s; });
    }

    fmt::print("Hello\n");
    fmt::print("Creating new movie\n");
    auto util = getUtility();
    util->usage();

    return 0;
}
