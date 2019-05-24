#pragma once
#include "Controller.hpp"

#include <string>
#include <vector>

namespace Pholos {

class Utility {
   public:
    Utility() = default;

    static void usage();
    static void getUserInput();
    static void help();

   private:
    inline static std::vector<std::string> commands_{
        "-h", "-x", "-c", "-a", "-e", "-d", "-s", "-q"
    };
    inline static std::vector<std::string> verboseCommands_{ "--help",   "--exit", "--create",
                                                             "--add",    "--edit", "--delete",
                                                             "--search", "--query" };
};
}  // namespace Pholos
