#include "application.hpp"
#include "movies.hpp"

using namespace Pholos;

//#if defined(_DEBUG)
//#endif

int main() {
  //#if defined(_DEBUG)
  //    Application app;
  //    app.runApplication();
  //
  //#else
  //    Application app;
  //    app.runApplication();
  //#endif
  Application app;
  app.init();
  app.run_application();

  return 0;
}
