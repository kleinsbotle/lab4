cmake_minimum_required(VERSION 3.13)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(lab4 main.cpp List.h Unit_tests.cpp Timetable.h Timetable.cpp)
target_link_libraries(lab4 gtest gtest_main)