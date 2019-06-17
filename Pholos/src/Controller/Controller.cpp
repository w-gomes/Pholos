#include "Controller.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../Application.hpp"
#include "../Stats.hpp"
#include "fmt/fmt.hpp"

namespace Pholos {

void Controller::goToMenu()
{
    auto app = getApplication();

    fmt::print("\n\nType [y] to continue or [n] to leave : ");
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
    // auto app = getApplication();

    fmt::print("Enter your option! Type [-h] for command list : ");
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
            this->addMenu();
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
        case Command::About:
            // Show application information
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
    } else if (command == "-A") {
        x = 7;
    }

    return x;
}

void Controller::exit()
{
    auto app = getApplication();
    app->exitApplication();
}

// TODO: Add instructions
void Controller::help()
{
    const std::string commands =
        fmt::format("- Usage:\n\n"
                    "\t -h \tshow help duh.\n"
                    "\t -x \texit application.\n"
                    "\t -a \tadd new object.(i.e., Movie or Tv Show). \n"
                    "\t -e \tedit existing objects.\n"
                    "\t -d \tdelete objects.\n"
                    "\t -s \tsearch.\n"
                    "\t -q \tquery (advanced searching.)\n"
                    "\t -A \tabout information about Pholos application.\n");

    fmt::print(commands);
}

// Add new movie or tvshow
void Controller::addMenu()
{
    auto app = getApplication();

    fmt::print("Movie [m] or Tv Show [t]?  : ");
    char userChoose;
    bool userChoice = false;

    do {
        std::cin >> userChoose;

        if (userChoose == 'm' || userChoose == 'M') {
            // call movie constructor.
            this->addMovie();
            userChoice = true;
        } else if (userChoose == 't' || userChoose == 'T') {
            // call tvshow constructor.
            this->addTvShow();
            userChoice = true;

        } else if (userChoose == 'c' || userChoose == 'C') {
            userChoice = true;
            app->exitApplication();
        } else {
            fmt::print("Wrong option! Enter [m] or [t].\n");
            fmt::print("Enter [c] to cancel. : ");
        }
    } while (!userChoice);
}

void Controller::addMovie()
{
    fmt::print("Adding a new Movie...\n"
               "Basic or Complete creation? : ");
    char optionCreation;
    std::cin >> optionCreation;
    std::cin.get();

    std::string name;
    double rating;
    int year;
    int stats = -1;

    if (optionCreation == 'b' || optionCreation == 'B') {
        fmt::print("Enter a name : ");
        std::getline(std::cin, name);
        std::cin.get();

        this->moviesList_.emplace_back(name);

    } else if (optionCreation == 'c' || optionCreation == 'C') {
        fmt::print("Enter a name, rating, and year. (Stats is optional)\n");

        fmt::print("Name : ");
        std::getline(std::cin, name);
        std::cin.get();
        fmt::print("Rating : ");
        std::cin >> rating;
        fmt::print("Year : ");
        std::cin >> year;

        fmt::print("Want to set stats? : ");
        char response;
        std::cin >> response;

        if (response == 'y' || response == 'Y') {
            fmt::print("\nStats. Plan to Watch [0], Watching [1], Completed [2], Dropped [3] : ");
            std::cin >> stats;
        }

        this->moviesList_.emplace_back(name, static_cast<double>(rating), static_cast<int>(year),
                                       static_cast<Stats>(stats));
    }

    fmt::print("New movie has been created!\n");
}

void Controller::addTvShow()
{
    fmt::print("Adding a new Tv Show...\n");
}
}  // namespace Pholos
