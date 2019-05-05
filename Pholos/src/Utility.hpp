#pragma once
#include "Controller.hpp"

#include <string>
#include <vector>

namespace Pholos {

class Utility {
   public:
    static Utility *instance;

    Utility();

    void usage();
    void run();
    void help();

   private:
    std::vector<std::string> commands_{ "-h", "-x", "-c", "-a", "-e", "-d", "-s", "-q" };
    std::vector<std::string> verboseCommands_{ "--help", "--exit",   "--create", "--add",
                                               "--edit", "--delete", "--search", "--query" };
};

Utility *getUtility();
}  // namespace Pholos
