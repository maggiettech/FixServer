#include <iostream>
#include "quickfix/SessionSettings.h"
#include "quickfix/FileStore.h"
#include "quickfix/SocketAcceptor.h"
#include "MyApplication.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    FIX::SessionSettings settings("/Users/maggietsui/CLionProjects/FixServer/config.cfg");

    MyApplication application;

    FIX::FileStoreFactory storeFactory( settings );
    FIX::ScreenLogFactory logFactory( settings );
    FIX::SocketAcceptor acceptor( application, storeFactory, settings, logFactory );

    acceptor.start();

    while (true) {
        std::cout << "application running ... " << std::endl;

        std::string value;
        std::cin >> value;

        if (value == "#quit") {
            break;
        } else {
            std::cout << "Received command: " << value << std::endl;
        }
    }

    acceptor.stop();

    return 0;
}
