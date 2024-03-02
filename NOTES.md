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
