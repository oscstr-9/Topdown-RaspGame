cmake_minimum_required(VERSION 3.18)
add_executable(app main.cpp)

target_link_libraries(app pthread)
