cmake_minimum_required(VERSION 3.20)

# Set project name
project(rpg C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

IF(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\dev\\SFML\\lib\\cmake\\SFML")
ENDIF()

#------------- CONFIGURATIONS

set(SOURCES src/main.cpp
        src/Characters.cpp
        src/Game.cpp
        src/GameState.cpp
        src/State.cpp

        include/Animation.h
        include/Characters.h
        include/Entity.h
        include/Game.h
        include/GameState.h
        include/Inanimated.h
        include/MapTiles.h
        include/State.h
        )

#------------- DEPENDENCIES


# SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

#------------- COMPILE
add_executable(rpg ${SOURCES})

#------------- LINK
target_include_directories(rpg PUBLIC include/ ${SFML_INCLUDE_DIR})
target_link_libraries(rpg sfml-graphics sfml-audio  ${SFML_DEPENDENCIES})


#------------- POST LINK
IF(WIN32)
    set(DLL_PATH "${PROJECT_SOURCE_DIR}/lib")
    # the following command copies SDL DLL to bin folder
    message("${PROJECT_SOURCE_DIR}")
    add_custom_command(TARGET rpg POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
           ${DLL_PATH}
           $<TARGET_FILE_DIR:rpg>)

    set(ASSETS_ORIGIN "${PROJECT_SOURCE_DIR}/assets")
    add_custom_command(TARGET rpg POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
           ${ASSETS_ORIGIN}
           $<TARGET_FILE_DIR:rpg>/../assets)
ENDIF()