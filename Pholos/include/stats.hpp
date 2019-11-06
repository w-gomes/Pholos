#pragma once

namespace Pholos {

// Rename this to a better name
enum class Stats
{
  NotSet      = -1,
  PlanToWatch = 0,
  Watching    = 1,
  Completed   = 2,
  Dropped     = 3
};
}  // namespace Pholos
