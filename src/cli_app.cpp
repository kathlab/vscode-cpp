#include <iostream>
#include "app.h"

using namespace std;

int main() {
    App app("Hello VS Code Test", "v1.0");

    cout << app.get_qualified_name() << '\n';

    return 0;
}