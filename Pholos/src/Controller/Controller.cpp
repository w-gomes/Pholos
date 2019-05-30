#include "Controller.hpp"
#include "fmt/fmt.hpp"

#include "Application.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace Pholos {

std::vector<std::string> Controller::commandsVector_{ "-h",     "-x",       "-c",       "-a",
                                                      "-e",     "-d",       "-s",       "-q",
                                                      "--help", "--exit",   "--create", "--add",
                                                      "--edit", "--delete", "--search", "--query" };

// XXX Incomplete
void Controller::proceedToMenu()
{
    auto app = getApplication();

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
}

// Refactor this
void Controller::menu()
{
    auto app = getApplication();
    fmt::print("Enter your option! Type --help or -h for command list : ");
    std::string command;
    std::cin >> command;

    auto findResult =
        std::find(Controller::commandsVector_.begin(), Controller::commandsVector_.end(), command);

    if (findResult == Controller::commandsVector_.end()) {
        fmt::print("Unknonw command!\n");
        return;
    }
    /*auto app = getApplication();

    bool gotAnswer    = false;
    bool commandFound = false;

    while (!commandFound) {
        std::string commandInput;
        fmt::print("Enter your option! (--help or -h for command list.) : ");
        std::cin >> commandInput;

        auto findResult =
            std::find(this->commandsVector_.begin(), this->commandsVector_.end(), commandInput);

        if (findResult == this->commandsVector_.end()) {
            fmt::print("Unknown command!");
            continue;
        }

        if ((*findResult == "-h") || (*findResult == "--help") {
            help();
                }

        if ((*findResult == "-x") || (*findResult == "--exit")) {
            app->exitApplication();
            break;
        }

        // Maybe unnecessary
        if (findResult != this->commandsVector_.end()) {
            commandFound = true;
        }
    }
    */
}

int Controller::getCommand(const std::string &command)
{
    int x = -1;
    if (command == "--help" || command == "-h") {
        x = 0;
    } else if (command == "--exit" || command == "-x") {
        x = 1;
    } else if (command == "--create" || command == "-c") {
        x = 2;
    } else if (command == "--add" || command == "-a") {
        x = 3;
    } else if (command == "--edit" || command == "-e") {
        x = 4;
    } else if (command == "--delete" || command == "-d") {
        x = 5;
    } else if (command == "--search" || command == "-s") {
        x = 6;
    } else if (command == "--query" || command == "-q") {
        x = 7;
    }

    return x;
}

void Controller::help()
{
    const std::string commands = fmt::format("- Usage:\n"
                                             "\t-Operations:\n\n"
                                             "\t -h or --help\n"
                                             "\t -x or --exit\n"
                                             "\t -c or --create\n\n\n"
                                             "\t -a or --add \n"
                                             "\t -e or --edit \n"
                                             "\t -d or --delete \n"
                                             "\t -s or --search \n"
                                             "\t -q or --query \n");

    fmt::print(commands);
}
}  // namespace Pholos
