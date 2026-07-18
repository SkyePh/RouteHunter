cmake_minimum_required(VERSION 4.2)
project(RouteHunter)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(RouteHunter main.cpp
        src/Platform.cpp
        src/Platform.h
        src/MainWindow.cpp
        src/MainWindow.h
        src/FFUFRunner.cpp)

target_link_libraries(RouteHunter PRIVATE Qt6::Widgets)
