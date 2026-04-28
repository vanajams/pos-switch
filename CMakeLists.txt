cmake_minimum_required(VERSION 3.16)
project(PosSwitch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Main executable
add_executable(pos_switch ${SOURCES})

# POS client simulator
add_executable(pos_client scripts/pos_client_simulator.cpp)

# Threads (IMPORTANT)
//find_package(Threads REQUIRED)
target_link_libraries(pos_switch PRIVATE Threads::Threads)
target_link_libraries(pos_client PRIVATE Threads::Threads)