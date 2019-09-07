#include "application.hpp"

#include "Movies/movies.hpp"
#include "fmt/fmt.hpp"

using namespace Pholos;

//#if defined(_DEBUG)
//#endif

int main()
{
    //#if defined(_DEBUG)
    //    Application app;
    //    app.runApplication();
    //
    //#else
    //    Application app;
    //    app.runApplication();
    //#endif
    Application app;
    app.runApplication();
    return 0;
}
