#pragma once

namespace Pholos {

class Movie;
class TvShow;
class User;
class Utility;

class Controller {
   public:
    static Controller *instance;

    Controller();
    void addMovie();

   private:
    Utility *utility_;
    Movie *movie_;
    TvShow *tvShow_;
    User *user_;
};

Controller *getController();
}  // namespace Pholos
