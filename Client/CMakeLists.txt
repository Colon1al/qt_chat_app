cmake_minimum_required(VERSION 3.5)
list(PREPEND CMAKE_FIND_LIBRARY_SUFFIXES .a .lib)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)


set(SOURCES
	Client.cpp
)

add_library(Client STATIC ${SOURCES})

target_link_libraries(Client Qt5::Core)
target_link_libraries(Client Qt5::Network)
target_include_directories(Client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})