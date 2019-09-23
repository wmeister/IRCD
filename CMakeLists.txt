cmake_minimum_required(VERSION 3.14)
project(IRCD)

set(CMAKE_CXX_STANDARD 14)

include_directories(IRCD)

add_executable(IRCD
        IRCD/IRCD/main.cpp
        IRCD/IRCD.sln)
