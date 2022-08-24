cmake_minimum_required(VERSION 3.5)

project(ver_catch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ver_catch main.cpp)
target_link_libraries(ver_catch -static  stdc++fs stdc++ gcc)
