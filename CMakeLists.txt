cmake_minimum_required(VERSION 3.22.1)
project(assignment0 LANGUAGES C CXX)

add_library(mmio mmio.c)
target_include_directories(mmio PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(main main.cpp)
target_link_libraries(main PUBLIC mmio)