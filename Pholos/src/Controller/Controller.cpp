#include "Controller.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../Application.hpp"
#include "fmt/fmt.hpp"

namespace Pholos {

void Controller::goToMenu()
{
    auto app = getApplication();

    fmt::print("Enter your user username : ");
    std::string name;
    std::cin >> name;

    // Check if user exists
    // Will look for username in a userlist, if not found, prompt creation option
    if (!getUser(name)) {
        fmt::print("\n\nType 'y' to continue or 'n' to leave : ");
        char response;
        std::cin >> response;
        if (response == 'n' || response == 'N') {
            // exit application
            app->exitApplication();
        } else if (response == 'y' || response == 'Y') {
            // this looks dumb
            return;
        }

        // Fix this, not working
    } else {
        fmt::print("\n\nUser not found!\n"
                   "Do you want to create a new User? : ");
        char response;
        std::cin >> response;
        if (response = 'n' || response == 'N') {
            app->exitApplication();
        } else if (response == 'y' || response == 'Y') {
            // calls createNewUser function
            this->createNewUser();
        }
    }
}

// Refactor this
void Controller::menu()
{
    // Maybe we don't need this.
    // auto app = getApplication();

    fmt::print("Enter your option! Type -h for command list : ");
    std::string command;
    std::cin >> command;

    auto findResult =
        std::find(this->commandsVector_.begin(), this->commandsVector_.end(), command);

    if (findResult == this->commandsVector_.end()) {
        fmt::print("command not found!\n");
        return;
    }

    int y = this->getCommand(command);
    assert(y != -1);
    switch (static_cast<Command>(y)) {
        case Command::Help:
            this->help();
            break;
        case Command::Exit:
            this->exit();
            break;
        case Command::Add:
            // Add new movie or tv show
            break;
        case Command::Edit:
            // Edit existing object
            break;
        case Command::Delete:
            // Delete a movie or a tvshow
            break;
        case Command::Search:
            // This search if movie exists
            break;
        case Command::Query:
            // This query for specific, i.e., query all movies watching
            // probly hard to implement
            break;
    }
}

int Controller::getCommand(const std::string &command)
{
    int x = -1;
    if (command == "-h") {
        x = 0;
    } else if (command == "-x") {
        x = 1;
    } else if (command == "-a") {
        x = 2;
    } else if (command == "-e") {
        x = 3;
    } else if (command == "-d") {
        x = 4;
    } else if (command == "-s") {
        x = 5;
    } else if (command == "-q") {
        x = 6;
    }

    return x;
}

void Controller::exit()
{
    auto app = getApplication();
    app->exitApplication();
}

void Controller::loadUsersList()
{
}

void Controller::createNewUser()
{
    std::string name;
    fmt::print("Enter a username : ");
    std::cin >> name;

    // @incomplete: if check if name taken

    Users user(name);
    this->addNewUser(user);
}

void Controller::addNewUser(const Users &user)
{
    this->usersList_.push_back(user);
}

// TODO: check if user exists
bool Controller::getUser(const std::string &name) const
{
    return true;
}

// TODO: Add instructions
void Controller::help()
{
    const std::string commands = fmt::format("- Usage:\n"
                                             "\t-Operations:\n\n"
                                             "\t -h\n"
                                             "\t -x\n"
                                             "\t -a\n"
                                             "\t -e\n"
                                             "\t -d\n"
                                             "\t -s\n"
                                             "\t -q\n");

    fmt::print(commands);
}
}  // namespace Pholos
