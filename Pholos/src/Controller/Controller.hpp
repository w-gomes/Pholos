#pragma once
#include <string>
#include <vector>

namespace Pholos {

class Controller {
    enum class Command
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
    static std::vector<std::string> commandsVector_;
};
}  // namespace Pholos
