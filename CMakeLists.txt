cmake_minimum_required(VERSION 3.9)
project(rpg C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

#------------- CONFIGURATIONS
# change this path to where you have SDL2
set(CMAKE_PREFIX_PATH "C:\\dev\\SDL2")

set(SOURCES src/main.cpp)

#------------- DEPENDENCIES
find_package(SDL2)
# Show paths found for SDL - this is mainly for debugging config/install of SDL2
message(" sdl2 include ${SDL2_INCLUDE_DIRS}" )
message(" sdl2 LIB ${SDL2_LIBRARIES}")

#------------- COMPILE
add_executable(rpg ${SOURCES})

#------------- LINK
target_include_directories(rpg PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(rpg ${SDL2_LIBRARIES})

#------------- POST LINK
# the following command copies SDL DLL to bin folder 
add_custom_command(TARGET rpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_INCLUDE_DIRS}/../lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:rpg>)