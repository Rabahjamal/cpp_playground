cmake_minimum_required(VERSION 3.16)
project(cpp_playground)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(templates)
add_subdirectory(concurrency)
add_subdirectory(sorting)
add_subdirectory(trie)
add_subdirectory(graph_algorithms)
