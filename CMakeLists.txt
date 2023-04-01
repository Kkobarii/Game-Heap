cmake_minimum_required(VERSION 3.25)
project(Game_Heap_Backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Target)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

if (NOT DISABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

add_compile_options(-Wall -Wextra -pedantic)

include_directories(API)
include_directories(BacklogOrganizer)
include_directories(Memory)
include_directories(Libs)
include_directories(Parsers)

find_package(restc-cpp REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    system
    program_options
    filesystem
    date_time
    context
    coroutine
    chrono
    log
    )

add_executable(Game_Heap_Backend
        main.cpp
        API/SteamAPI.h
        API/SteamAPI.cpp
        API/HowLongToBeatAPI.h
        API/HowLongToBeatAPI.cpp
        BacklogOrganizer/Game.h
        BacklogOrganizer/Game.cpp
        BacklogOrganizer/GameLibrary.h
        BacklogOrganizer/GameLibrary.cpp
        BacklogOrganizer/BacklogOrganizer.h
        BacklogOrganizer/BacklogOrganizer.cpp
        Memory/DataManager.h
        Memory/DataManager.cpp
        Parsers/APIParser.h
        Parsers/APIParser.cpp
        Parsers/JSONParser.h
        Parsers/JSONParser.cpp)

target_link_libraries(Game_Heap_Backend
    ${RESTC_CPP_LIBRARIES}
    ${Boost_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    )

target_include_directories(Game_Heap_Backend PUBLIC
    $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}/build>
    $<BUILD_INTERFACE:${OPENSSL_INCLUDE_DIR}>
    )
