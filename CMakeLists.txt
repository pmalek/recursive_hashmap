cmake_minimum_required(VERSION 2.8)
project(recursive CXX)

IF(( NOT CMAKE_BUILD_TYPE) OR (CMAKE_BUILD_TYPE STREQUAL "Release"))
  message(STATUS "Release build.")
  SET( CMAKE_BUILD_TYPE "Release")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Debug build.")
  SET( CMAKE_BUILD_TYPE "Debug")
ELSE()
  message( FATAL_ERROR "Unknown build type!!! \"" ${CMAKE_BUILD_TYPE} "\"")
ENDIF()

set(SOURCE_DIRECTORY src)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11")
include_directories(${SOURCE_DIRECTORY})

file(GLOB SOURCE_FILES ${SOURCE_DIRECTORY}/*.cpp)

add_executable(recursive ${SOURCE_FILES})

################################################
#################### TESTS #####################
################################################
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

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
