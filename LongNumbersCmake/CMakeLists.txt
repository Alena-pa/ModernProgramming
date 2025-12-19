cmake_minimum_required(VERSION 3.14)
project(LongNumberProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(longnumber main/longNumber.cpp)

target_include_directories(longnumber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/main)

add_executable(longnumber_tests tests/test.cpp)

target_link_libraries(longnumber_tests longnumber gtest_main)

enable_testing()
add_test(NAME LongNumberTests COMMAND longnumber_tests)