cmake_minimum_required(VERSION 3.25)
project(Game_Heap)

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
include_directories(Output)

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

add_executable(gameheap
        main.cpp
        API/SteamAPI.cpp
        API/HowLongToBeatAPI.cpp
        BacklogOrganizer/Game.cpp
        BacklogOrganizer/GameLibrary.cpp
        BacklogOrganizer/GameFinder.cpp
        Memory/DataManager.cpp
        Parsers/APIParser.cpp
        Parsers/JSONParser.cpp
        BacklogOrganizer/PriorityCalculator.cpp
        Output/Logger.cpp
        Output/Printer.cpp
        )

target_link_libraries(gameheap
    ${RESTC_CPP_LIBRARIES}
    ${Boost_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    )

target_include_directories(gameheap PUBLIC
    $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}/build>
    $<BUILD_INTERFACE:${OPENSSL_INCLUDE_DIR}>
    )
