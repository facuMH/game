cmake_minimum_required(VERSION 3.20)

# Set project name
project(rpg C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

IF(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\dev\\SFML\\lib\\cmake\\SFML")
    set(CMAKE_CXX_FLAGS "/MP /EHsc")
ENDIF()

#------------- CONFIGURATIONS

set(SOURCES src/main.cpp
        src/Button.cpp
        src/CombatState.cpp
        src/DialogueBox.cpp
        src/Enemy.cpp
        src/Game.cpp
        src/GameOverState.cpp
        src/GameState.cpp
        src/HouseManager.cpp
        src/InteractionManager.cpp
        src/InventoryState.cpp
        src/ItemManager.cpp
        src/MainMenuState.cpp
        src/PauseGameState.cpp
        src/Player.cpp
        src/SettingsState.cpp
        src/State.cpp
        src/Tile.cpp
        src/TileMap.cpp)

set(HEADERS include/Animation.h
        include/asset_data.h
        include/AssetsManager.h
        include/AssetsPaths.h
        include/Button.h
        include/definitions.h
        include/DialogueBox.h
        include/Enemy.h
        include/entity_attributes/Combatant.h
        include/entity_attributes/Movement.h
        include/entity_attributes/SteeredMovement.h
        include/entity_attributes/IdleMovement.h
        include/Game.h
        include/House.h
        include/HouseManager.h
        include/Inanimated.h
        include/InteractionManager.h
        include/ItemManager.h
        include/Player.h
        include/State.h
        include/Tile.h
        include/TileMap.h
        include/Villager.h
        include/Entity.h
        include/states/CombatState.h
        include/states/GameState.h
        include/states/GameOverState.h
        include/states/InventoryState.h
        include/states/MainMenuState.h
        include/states/PauseGameState.h
        include/states/SettingsState.h)

set(DEPENDENCIES libs/tileson.hpp)

#------------- DEPENDENCIES


# SFML
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

#------------- COMPILE
add_executable(rpg ${SOURCES} ${HEADERS} ${DEPENDENCIES})

#------------- LINK
target_include_directories(rpg PUBLIC include/ ${SFML_INCLUDE_DIR})
target_include_directories(rpg PUBLIC libs/ ${SFML_INCLUDE_DIR})
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

    set(CONFIG_ORIGIN "${PROJECT_SOURCE_DIR}/config")
    add_custom_command(TARGET rpg POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
           ${CONFIG_ORIGIN}
           $<TARGET_FILE_DIR:rpg>/../config)
ENDIF()
