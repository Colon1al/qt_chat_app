cmake_minimum_required(VERSION 3.5)

project(qt_chat_app LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)
find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(App)