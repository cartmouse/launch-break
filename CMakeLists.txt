cmake_minimum_required(VERSION 3.0)

project(launch-break)

add_definitions(-D__WINDOWS_MM__)

add_executable(launch-break main.cpp RtMidi.cpp portHandler.cpp lpx.cpp)

target_link_libraries(launch-break winmm)