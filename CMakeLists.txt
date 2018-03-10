cmake_minimum_required(VERSION 3.9)
project(PROCEDURAL_ISLAND)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AssetManager.cpp AssetManager.h FastNoise.cpp FastNoise.h Terrain.cpp Terrain.h)
add_executable(PROCEDURAL_ISLAND ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PROCEDURAL_ISLAND ${SFML_LIBRARIES})
endif()
