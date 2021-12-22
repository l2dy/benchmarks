cmake_minimum_required(VERSION 2.8.12)
project(benchmarks)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

foreach(bench flb-nano)
  add_executable(${bench} src/${bench}.cpp)
  target_link_libraries(${bench} ${CONAN_LIBS})
endforeach()
