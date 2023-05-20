cmake_minimum_required(VERSION 3.10)

project(snow)

# add_library(snow
#     STATIC
#         ${PROJECT_SOURCE_DIR}/include/static/*.cpp)

target_include_directories(snow
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(snow_main main.cpp)

target_link_directories(snow_main
    PRIVATE
        snow
)