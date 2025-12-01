add_library(df STATIC)

target_include_directories(df PUBLIC ..)

target_link_libraries(df PUBLIC nlohmann_json::nlohmann_json csv gcov)

target_sources(df PRIVATE csv_config.cpp)

target_compile_options(df PRIVATE -Wall -Wextra -Wpedantic)

target_compile_options(df PUBLIC -std=c++20)

