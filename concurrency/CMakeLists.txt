add_executable(concurrency main.cpp)

target_link_libraries(concurrency PRIVATE pthread)
