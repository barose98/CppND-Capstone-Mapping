cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(capstone-mapping)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0) 
pkg_check_modules(CAIROMM cairomm-1.0) 
pkg_check_modules(LIBCURL libcurl) 
pkg_check_modules(EXPAT expat) 

include_directories(${GTKMM_INCLUDE_DIRS} ${CAIROMM_INCLUDE_DIRS} ${LIBCURL_INCLUDE_DIRS} ${EXPAT_INCLUDE_DIRS} ./include)

file(GLOB SOURCES "src/*.cpp")

add_executable(capstone-mapping ${SOURCES})

configure_file("capstone-mapping.glade" "capstone-mapping.glade"  COPYONLY)

set_property(TARGET capstone-mapping PROPERTY CXX_STANDARD 17)
target_link_libraries(capstone-mapping ${GTKMM_LINK_LIBRARIES} ${LIBCURL_LINK_LIBRARIES} ${EXPAT_LINK_LIBRARIES} stdc++fs pthread)
# TODO: Run -Werror in CI.
target_compile_options(capstone-mapping PRIVATE -Wall -Wextra)
