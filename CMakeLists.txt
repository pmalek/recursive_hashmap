cmake_minimum_required(VERSION 2.8)
project(recursive CXX)

set(SOURCE_DIRECTORY src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
include_directories(${SOURCE_DIRECTORY})

file(GLOB SOURCE_FILES ${SOURCE_DIRECTORY}/*.cpp)

add_executable(recursive ${SOURCE_FILES})

################################################
#################### TESTS #####################
################################################
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

enable_testing()

# maybe https://github.com/triglav/cmake-findgmock ? for gmock?
set(GMOCK_ROOT PUT_YOUR_GMOCK_DIR_HERE)
# put gtest root directory inside gmock_root dir - at least this way it built for me...
set(GTEST_ROOT ${GMOCK_ROOT}/gtest)
set(TEST_SOURCE_DIRECTORY test/src)

find_package(GTest REQUIRED)

# ${GTEST_INCLUDE_DIRS} is an output from find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GMOCK_ROOT}/include)

file(GLOB TEST_SOURCE_FILES ${TEST_SOURCE_DIRECTORY}/*.cpp)

add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCE_FILES})

target_link_libraries(${PROJECT_TEST_NAME}
    ${GTEST_BOTH_LIBRARIES}
    ${GMOCK_ROOT}/libgmock.a
    pthread)
