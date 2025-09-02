cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BankAccountSystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable and specify its source files
add_executable(bank_system src/main.cpp src/BankAccount.cpp src/utils.cpp)
