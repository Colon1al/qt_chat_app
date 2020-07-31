cmake_minimum_required(VERSION 3.5)

list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

set(SOURCES
	Server.cpp
	main.cpp
)


add_executable(Server ${SOURCES})

target_link_libraries(Server Qt5::Core)
target_link_libraries(Server Qt5::Network)
