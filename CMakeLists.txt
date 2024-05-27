cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Tables)
project(${PROJECT_NAME})

set(PROJ_LIBRARY "${PROJECT_NAME}")

include_directories(include)

add_subdirectory(src)
add_subdirectory(samples)