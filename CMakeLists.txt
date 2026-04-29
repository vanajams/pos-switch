cmake_minimum_required(VERSION 3.16)
project(PosSwitch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(pos_switch ${SOURCES})

add_executable(pos_client scripts/pos_client_simulator.cpp)

find_package(Threads REQUIRED)

#target_link_libraries(pos_switch PRIVATE Threads::Threads)
#target_link_libraries(pos_client PRIVATE Threads::Threads)

target_link_libraries(pos_switch PRIVATE Threads::Threads ws2_32)
target_link_libraries(pos_client PRIVATE Threads::Threads ws2_32)