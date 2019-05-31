#pragma once
#include <string>
#include <vector>

namespace Pholos {

class Controller {
    enum class Command
    {
        Help   = 0,
        Exit   = 1,
        Add    = 2,
        Edit   = 3,
        Delete = 4,
        Search = 5,
        Query  = 6
    };

   public:
    Controller() = default;

    Controller(const Controller &obj) = delete;
    Controller &operator=(const Controller &obj) = delete;
    Controller(const Controller &&obj)           = delete;
    Controller &operator=(const Controller &&obj) = delete;

    ~Controller() = default;

    void goToMenu();  // This needs a better name
    void menu();
    void help();
    void exit();
    int getCommand(const std::string &command);

   private:
    Command commands_;
    std::vector<std::string> commandsVector_{ "-h", "-x", "-a", "-e", "-d", "-s", "-q" };
};
}  // namespace Pholos
