add_library(uiutils STATIC)

target_sources(uiutils PRIVATE ui_utils.cpp)

target_include_directories(uiutils PUBLIC ..)

target_compile_options(uiutils PRIVATE -Wall -Wextra -Wpedantic -std=c++20)
