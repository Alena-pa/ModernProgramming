cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Alena/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(LongNumbersCmake)

add_subdirectory(main)
add_subdirectory(tests)
add_library(longnumber main/longNumber.cpp)
target_include_directories(longnumber PUBLIC main)