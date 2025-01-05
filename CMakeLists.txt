cmake_minimum_required(VERSION 3.12)

project(TableManager)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/mocks)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(TableManager
    src/main.cpp
    src/ClientManager.cpp
    src/TableManager.cpp
    src/EventManager.cpp
    utils/TimeUtil.cpp
)

target_include_directories(TableManager PUBLIC "${CMAKE_SOURCE_DIR}/include")

enable_testing()

add_executable(EventManagerTests
    tests/EventManagerTests.cpp
    mocks/MockClientManager.h
    mocks/MockTableManager.h
    src/ClientManager.cpp
    src/TableManager.cpp
    src/EventManager.cpp
    utils/TimeUtil.cpp
)
target_link_libraries(EventManagerTests
    GTest::gmock_main
)

add_executable(ClientManagerTests
    src/ClientManager.cpp
    utils/TimeUtil.cpp
)
target_link_libraries(ClientManagerTests
    GTest::gtest_main
)

add_executable(TableManagerTests
    src/TableManager.cpp
    utils/TimeUtil.cpp
)
target_link_libraries(TableManagerTests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(EventManagerTests)
gtest_discover_tests(ClientManagerTests)
gtest_discover_tests(TableManagerTests)
