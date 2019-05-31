#include "Controller.hpp"
#include "fmt/fmt.hpp"

#include "Application.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace Pholos {

std::vector<std::string> Controller::commandsVector_{
    "-h", "-x", "-c", "-a", "-e", "-d", "-s", "-q"
};

void Controller::goToMenu()
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
    // Maybe we don't need this.
    auto app = getApplication();

    fmt::print("Enter your option! Type -h for command list : ");
    std::string command;
    std::cin >> command;

    auto findResult =
        std::find(Controller::commandsVector_.begin(), Controller::commandsVector_.end(), command);

    if (findResult == Controller::commandsVector_.end()) {
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
    if (command == "-h") {
        x = 0;
    } else if (command == "-x") {
        x = 1;
    } else if (command == "-c") {
        x = 2;
    } else if (command == "-a") {
        x = 3;
    } else if (command == "-e") {
        x = 4;
    } else if (command == "-d") {
        x = 5;
    } else if (command == "-s") {
        x = 6;
    } else if (command == "-q") {
        x = 7;
    }

    return x;
}

void Controller::exit()
{
    auto app = getApplication();
    app->exitApplication();
}

void Controller::help()
{
    const std::string commands = fmt::format("- Usage:\n"
                                             "\t-Operations:\n\n"
                                             "\t -h\n"
                                             "\t -x\n"
                                             "\t -c\n"
                                             "\t -a\n"
                                             "\t -e\n"
                                             "\t -d\n"
                                             "\t -s\n"
                                             "\t -q\n");

    fmt::print(commands);
}
}  // namespace Pholos
