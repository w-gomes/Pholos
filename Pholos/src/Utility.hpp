#pragma once

namespace Pholos {

class Utility {
   public:
    static Utility *instance;

    Utility();

    void usage();
};

Utility *getUtility();
}  // namespace Pholos
