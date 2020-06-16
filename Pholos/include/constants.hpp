#pragma once

namespace Pholos {

enum class Command {
  Unknown = -1,
  Help    = 0,
  Exit    = 1,
  Add     = 2,
  Edit    = 3,
  Delete  = 4,
  Search  = 5,
  About   = 6,
  List    = 7,
  Cmd     = 8
};

enum class Type { TvShow, Movie };

enum Width : std::size_t {
  Stat          = 13,
  Rating        = 6,
  ID            = 8,
  Episode       = 7,
  Total_Episode = 14
};

enum class Stats {
  NotSet      = -1,
  Watching    = 1,
  PlanToWatch = 2,
  Completed   = 3,
  Dropped     = 4
};
}  // namespace Pholos
