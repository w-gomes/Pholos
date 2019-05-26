#include "Utility.hpp"
#include "fmt/fmt.hpp"

#include "Application.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace Pholos {

// This is the first thing that is called when application runs
void Utility::menu()
{
    const std::string logo = fmt::format("\n\t:::::::::::::::::"
                                         "\n\t::::::::::::::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t:::::        ::::::"
                                         "\n\t::::::::::::::::::"
                                         "\n\t:::::::::::::::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::"
                                         "\n\t:::::\n\n");

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

    fmt::print("\n\tWelcome to Pholos!\n");
    fmt::print(logo);
    fmt::print(commands);

    auto app = getApplication();

    fmt::print("\n\nDo you wish to proceed?(y|n) : ");
    char response;
    std::cin >> response;
    if (response == 'y' || response == 'Y') {
        // call getUserInput();
        getUserInput();
    } else if (response == 'n' || response == 'N') {
        // Close the application
        app->close();
    }
}

void Utility::getUserInput()
{
    // ask for user input
    auto app = getApplication();

    fmt::print("Enter your option! (--help or -h for command list.) : ");
    bool runAnswer = true;
    std::string answer;
    do {
        std::cin >> answer;
        auto findResult =
            std::find(this->commandsVector_.begin(), this->commandsVector_.end(), answer);
        if (findResult == this->commandsVector_.end()) {
            fmt::print("Unknown command. Type --help or -h for help. : ");
            continue;
        }

        if ((*findResult == "-x") || (*findResult == "--exit")) {
            runAnswer = false;
        }

        int code = getCommand(*findResult);
        assert(code != -1);

        switch (code) {
            case 0:
                // Help
                help();
                break;
            case 1:
                // Exit
                runAnswer = false;
                break;
            case 2:
                // Create
                break;
            case 3:
                // Add
                break;
            case 4:
                // Edit
                break;
            case 5:
                // Delete
                break;
            case 6:
                // Search
                break;
            case 7:
                // Query
                break;
            default:
                fmt::print("hellO");
                break;
        }

    } while (runAnswer);

    app->close();
}

int Utility::getCommand(const std::string &command)
{
    if (command == "--help" || command == "-h") {
        return 0;
    } else if (command == "--exit" || command == "-x") {
        return 1;
    } else if (command == "--create" || command == "-c") {
        return 2;
    } else if (command == "--add" || command == "-a") {
        return 3;
    } else if (command == "--edit" || command == "-e") {
        return 4;
    } else if (command == "--delete" || command == "-d") {
        return 5;
    } else if (command == "--search" || command == "-s") {
        return 6;
    } else if (command == "--query" || command == "-q") {
        return 7;
    }

    return -1;
}  // namespace Pholos

void Utility::help()
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
