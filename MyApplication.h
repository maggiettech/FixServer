//
// Created by Maggie Tsui on 2/3/2024.
//

#ifndef FIXSERVER_MYAPPLICATION_H
#define FIXSERVER_MYAPPLICATION_H

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Utility.h"

class MyApplication
    : public FIX::Application,
      public FIX::MessageCracker
{
    void onCreate( const FIX::SessionID& sessionID ) {}
    void onLogon( const FIX::SessionID& sessionID );
    void onLogout( const FIX::SessionID& sessionID );
    void toAdmin( FIX::Message& message, const FIX::SessionID& sessionID );
    void toApp( FIX::Message& message, const FIX::SessionID& sessionID ) QUICKFIX_THROW ( DoNotSend ) {}
    void fromAdmin( const FIX::Message& message, const FIX::SessionID& sessionID ) QUICKFIX_THROW( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {}
    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )  QUICKFIX_THROW( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {}
};


#endif //FIXSERVER_MYAPPLICATION_H
