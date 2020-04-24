cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Mapping)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0) 
pkg_check_modules(CAIROMM cairomm-1.0) 
pkg_check_modules(CAIROMMSVG cairomm-svg-1.0) 
pkg_check_modules(XERCES xerces-c) 

include_directories(${GTKMM_INCLUDE_DIRS} include)
include_directories(${CAIROMM_INCLUDE_DIRS} include)
include_directories(${CAIROMMSVG_INCLUDE_DIRS} include)
include_directories(${XERCES_INCLUDE_DIRS} include)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(mapping ${SOURCES})

set_property(TARGET mapping PROPERTY CXX_STANDARD 17)
target_link_libraries(mapping ${GTKMM_LINK_LIBRARIES} stdc++fs pthread)
# TODO: Run -Werror in CI.
target_compile_options(mapping PRIVATE -Wall -Wextra)
