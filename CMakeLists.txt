cmake_minimum_required(VERSION 4.2)
project(RouteHunter)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(app_icon_asset "")

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE RouteHunter512.icns)
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/assets/RouteHunter512.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")
    set(app_icon_asset ${app_icon_macos})
elseif(WIN32)
    set(app_icon_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/RouteHunter.rc"
            src/FFUFCommand.h
            src/FFUFCommand.h)
endif()

qt_add_executable(RouteHunter
        main.cpp
        src/Platform.cpp
        src/Platform.h
        src/MainWindow.cpp
        src/MainWindow.h
        src/FFUFRunner.cpp
        ${app_icon_asset}
        src/FFUFCommand.h)

if(APPLE)
    set_target_properties(RouteHunter PROPERTIES MACOSX_BUNDLE TRUE)
endif()

add_custom_command(TARGET RouteHunter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/wordlists"
        "$<TARGET_FILE_DIR:RouteHunter>/wordlists"
        COMMENT "Copy wordlists next to executable")

qt_add_resources(RouteHunter "app_icons"
        PREFIX "/"
        FILES assets/RouteHunter.png)

target_link_libraries(RouteHunter PRIVATE Qt6::Widgets)
