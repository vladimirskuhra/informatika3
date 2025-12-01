cmake_minimum_required(VERSION 3.19)

project(data-processor
    VERSION     0.0.1
    DESCRIPTION "Project with a library and executables to process data"
    LANGUAGES   CXX
)

add_subdirectory(external)

add_subdirectory(libdf)

add_subdirectory(weather)
