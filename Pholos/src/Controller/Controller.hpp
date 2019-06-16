#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../User/User.hpp"

namespace Pholos {

class Users;

class Controller {
    enum class Command
    {
        Help   = 0,
        Exit   = 1,
        Add    = 2,
        Create = 3,
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
    void loadUsersList();
    int getCommand(const std::string &command);
    void createNewUser();
    void addNewUser(const Users &user);
    bool getUser(const std::string &name) const;

   private:
    Command commands_;
    std::vector<std::string> commandsVector_{ "-h", "-x", "-a", "-c", "-e", "-d", "-s", "-q" };
    std::vector<Users> usersList_;
};
}  // namespace Pholos
