//
// Created by Maggie Tsui on 2/3/2024.
//

#include "MyApplication.h"

void MyApplication::onLogon( const FIX::SessionID& sessionID ) {
    std::cout << "Log on from: " << sessionID << std::endl;
}

void MyApplication::onLogout( const FIX::SessionID& sessionID ) {
    std::cout << "Log out from: " << sessionID << std::endl;
}
void MyApplication::toAdmin( FIX::Message& message, const FIX::SessionID& sessionID) {
    std::cout << "toAdmin: " << message << ", sessionID: " << sessionID << std::endl;
}