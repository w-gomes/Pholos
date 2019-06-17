#pragma once

// for debug purpose
#include <iostream>

#include <memory>
#include <string>
#include <vector>

#include "../Movie/Movie.hpp"
#include "../TvShow/TvShow.hpp"

namespace Pholos {

class Users;

class Controller {
    enum class Command
    {
        Help   = 0,
        Exit   = 1,
        Add    = 2,
        Edit   = 3,
        Delete = 4,
        Search = 5,
        Query  = 6,
        About  = 7
    };

   public:
    Controller() = default;

    Controller(const Controller &obj) = delete;
    Controller &operator=(const Controller &obj) = delete;
    Controller(const Controller &&obj)           = delete;
    Controller &operator=(const Controller &&obj) = delete;

    // For debugging purpose...
    // after return this to default.
    ~Controller()
    {
        std::cout << "\n...Calling Controller destructor...\n";
    }

    void goToMenu();  // This needs a better name
    void menu();
    void help();
    void exit();
    void addMenu();
    int getCommand(const std::string &command);

    void addMovie();
    void addTvShow();

   private:
    Command commands_;
    std::vector<std::string> commandsVector_{ "-h", "-x", "-a", "-e", "-d", "-s", "-q", "-A" };
    std::vector<Movies> moviesList_;
    std::vector<TvShow> tvShowList_;
};
}  // namespace Pholos
