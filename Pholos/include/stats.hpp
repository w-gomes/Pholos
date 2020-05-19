#pragma once

namespace Pholos {

// Rename this to a better name
enum class Stats {
  NotSet      = -1,
  Watching    = 1,
  PlanToWatch = 2,
  Completed   = 3,
  Dropped     = 4
};
}  // namespace Pholos
