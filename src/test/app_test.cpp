#include "doctest.h"
#include "../app.h"

TEST_SUITE_BEGIN("App");
TEST_CASE("create app, get_qualified_name") 
{
    App app{"Test App", "v1.0"};
    CHECK(app.get_name() == "Test App");
    CHECK(app.get_version() == "v1.0");
    CHECK(app.get_qualified_name() == "Test App v1.0");
}
TEST_SUITE_END();
