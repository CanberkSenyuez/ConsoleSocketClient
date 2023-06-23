cmake_minimum_required(VERSION 3.25)
project(ConsoleSocketClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsoleSocketClient main.cpp)

# Link against the necessary libraries
target_link_libraries(ConsoleSocketClient PRIVATE Ws2_32)
