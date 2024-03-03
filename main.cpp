#include <iostream>
#include "quickfix/SessionSettings.h"
#include "MyApplication.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    FIX::SessionSettings settings("/Users/maggietsui/CLionProjects/FixServer/config.cfg");

    MyApplication application;

    return 0;
}
