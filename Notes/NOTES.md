# Notes

## Steps to set up project

Set Up:
- MacOS
- CLion IDE

### Create Project
- File > New > Project > C++ Executable > C++20 for Language Standard 
- CMakeLists.txt and main.cpp will be automatically created and running FixServer application should work out of the box (prints "Hello, World!")

### Set Up Git
* Create README.md
* Version control (top of IDE) > Create Git Repository
* Add created files to Git
* Create empty repository on Git
* Specify remote url https://github.com/maggiettech/FixServer.git then push

### Include quickfix library using vcpkg
References:
GitHub: https://github.com/quickfix/quickfix

Website: https://quickfixengine.org/c/documentation/

* View > Tool Window > Vcpkg
* Click on '+' to add Vcpkg repository (it basically clones a fresh vcpkg repo locally so you can install any packages available through vcpkg later)
* Check 'Add vcpkg integration to existing CMake profiles'
* Install quickfix through the extension
* Once installed should get a hint suggesting you to add to CMakeLists.txt 
    ``` 
    find_package(quickfix CONFIG REQUIRED)
    target_link_libraries(main PRIVATE quickfix)
    ```
* First param in target_link_libraries should be equal to first param in add_executable(FixServer main.cpp) i.e. your application/executable name

## Implementing quickfix/Application.h

To have a FIX application up and running, a few methods have to be overriden.

Start Date: March 2 2024
Target End Date: March 10 2024

```
  virtual void onCreate( const SessionID& ) = 0;
  
  /// Notification of a session successfully logging on
  virtual void onLogon( const SessionID& ) = 0;
  
  /// Notification of a session logging off or disconnecting
  virtual void onLogout( const SessionID& ) = 0;
  
  /// Notification of admin message being sent to target
  virtual void toAdmin( Message&, const SessionID& ) = 0;
  
  /// Notification of app message being sent to target
  virtual void toApp( Message&, const SessionID& )
  QUICKFIX_THROW( DoNotSend ) = 0;
  
  /// Notification of admin message being received from target
  virtual void fromAdmin( const Message&, const SessionID& )
  QUICKFIX_THROW( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) = 0;
  
  /// Notification of app message being received from target
  virtual void fromApp( const Message&, const SessionID& )
  QUICKFIX_THROW( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) = 0;
```

### Class Inheritance Issue

```
// quickfix library:
  class Application {
  public:
    virtual void onLogon( const SessionID& ) = 0;
  }

// my project:

MyApplication.h
  class MyApplication
    : FIX::Application,
      FIX::MessageCracker
  {
      void onLogout( const FIX::SessionID& sessionID ) {}
  }

MyApplication.c

  #include "MyApplication.h"
  
  void MyApplication::onLogout( const FIX::SessionID& sessionID ) {
      std::cout << "Log out from: " << sessionID << std::endl;
  }
  
IDE is going to complain "Redefinition of 'onLogout'"
```

correction:
```
// incorrect
void MyApplication::onLogout( const FIX::SessionID& sessionID ) {}
-->
// correct
void MyApplication::onLogout( const FIX::SessionID& sessionID );
```
Definition vs declaration
* The former is a definition, so if you specify that in the header file you've provided an implementation, and if you try to do ```void MyApplication::onLogout ( ... ) {} ``` again in the source file (MyApplication.cpp) then you are redefining the function 
* Latter is declaration, so implementation / definition can now go in the source file

### Exception Handling syntax

In Utility.h of quickfix library
```
#define QUICKFIX_THROW(...) noexcept
```
This is an example of a macro
* ```#define``` is a directive / preprocessor command specifying that this is a macro
* ```(...)``` means the macro is going to behave like a function and will take a varying number of arguments (the ellipsis)
* ```noexcept``` means function will not throw an exception (for compiler optimization)

#### quickfix/Application.h
```
void toApp( Message& message, const SessionID& sessionID )
QUICKFIX_THROW( DoNotSend )
```

#### Utility.h
```
#ifdef __cpp_noexcept_function_type
#define QUICKFIX_THROW(...) noexcept
#else
#define QUICKFIX_THROW(...) throw(__VA_ARGS__)
#endif
```

#### Exception.h
```
// definition of DoNotSend
/// Indicates user does not want to send a message
struct DoNotSend : public Exception
{
  DoNotSend( const std::string& what = "" )
    : Exception( "Do Not Send Message", what ) {}
};

/// Base QuickFIX exception type.
struct Exception : public std::logic_error
{
  Exception( const std::string& type, const std::string& detail )
  : std::logic_error( detail.size() ? type + ": " + detail : type),
    type( type ), detail( detail )
  {}
  ~Exception() NOEXCEPT {}

  std::string type;
  std::string detail;
};

```

### Starting the application

#### Class inheritance issue
When creating class that inherits from another class:
```
class  <derived_class_name> : <access-specifier> <base_class_name>
```
Access specifier --> if not specified it's private by default

IDE complaining:
```
class MyApplication
    : FIX::Application, --> implicitly private
      FIX::MessageCracker
Cannot cast 'MyApplication' to its private base class 'FIX::Application'
```

SocketAcceptor expects FIX::Application. We're passing in MyApplication class which inherits from FIX::Application, but we have implicitly specified access specifier as private so we cannot cast it to base class FIX::Application
```
FIX::SocketAcceptor acceptor( application, storeFactory, settings, logFactory );
```

#### Creating a socket
```
FIX::FileStoreFactory storeFactory( settings );
FIX::ScreenLogFactory logFactory( settings );
FIX::SocketAcceptor acceptor( application, storeFactory, settings, logFactory );

acceptor.start();
```

#### FIX::ConfigError: Configuration failed: No sessions defined for acceptor
Set a few breakpoints and found issues in Acceptor.cpp class when initializing the acceptor.
Root cause was because in the config file:
```
[DEFAULT]
ConnectionType=acceptor
```
ConnectionType was specified to be initiator instead of acceptor. So there were no configs for acceptors

#### FIX::ConfigError: Configuration failed: DataDictionary not defined

Question - if I wanted to debug DataDictionary.cpp but that's in the library --> can i set a breakpoint there? how does it work? 
/Users/maggietsui/CLionProjects/vcpkg/buildtrees/quickfix/src/v1.15.1-b3b42dfc02.clean/src/C++/Acceptor.cpp

