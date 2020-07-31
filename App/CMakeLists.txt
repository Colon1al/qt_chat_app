cmake_minimum_required(VERSION 3.5)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(App
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )

target_link_libraries(App Qt5::Widgets)
target_link_libraries(App Client)