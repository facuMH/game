cmake_minimum_required(VERSION 3.9)
project(rpg LANGUAGE CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

#------------- CONFIGURATIONS


#------------- DEPENDENCIES
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

#------------- COMPILE
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(rpg main.cpp)

#------------- LINK
target_link_libraries(rpg ${SDL2_LIBRARIES})
