cmake_minimum_required(VERSION 3.20)

# Set project name
project(rpg C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

#------------- CONFIGURATIONS

set(SOURCES src/main.cpp
        src/Game.cpp
        headers/Game.h
        src/State.cpp
        headers/State.h
        src/GameState.cpp
        headers/GameState.h)

#------------- DEPENDENCIES

# SDL
find_package(SDL2)
# Show paths found for SDL - this is mainly for debugging config/install of SDL2
message(" sdl2 include ${SDL2_INCLUDE_DIRS}" )
message(" sdl2 LIB ${SDL2_LIBRARIES}")

# SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

#------------- COMPILE
add_executable(rpg ${SOURCES})

#------------- LINK
target_include_directories(rpg PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(rpg ${SDL2_LIBRARIES} sfml-graphics sfml-audio)

#------------- POST LINK
# the following command copies SDL DLL to bin folder 
# add_custom_command(TARGET rpg POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${SDL2_INCLUDE_DIRS}/../lib/x64/SDL2.dll"
#        $<TARGET_FILE_DIR:rpg>)