#pragma once
#include "Controller.hpp"

#include <string>
#include <vector>

namespace Pholos {

class Utility {
    enum Command
    {
        Help   = 0,
        Exit   = 1,
        Create = 2,
        Add    = 3,
        Edit   = 4,
        Delete = 5,
        Search = 6,
        Query  = 7
    };

   public:
    Utility() = default;

    void menu();
    void getUserInput();
    void help();
    int getCommand(const std::string &command);

   private:
    Command commands_;
    inline static std::vector<std::string> commandsVector_{
        "-h",     "-x",     "-c",       "-a",    "-e",     "-d",       "-s",       "-q",
        "--help", "--exit", "--create", "--add", "--edit", "--delete", "--search", "--query"
    };
};
}  // namespace Pholos
