include(FetchContent)

FetchContent_Declare(
    lib-csv-parser
    GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser
    GIT_TAG master
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/csv-parser
)

FetchContent_Declare(
    lib-nlohmann
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann
)

FetchContent_MakeAvailable(lib-csv-parser)

FetchContent_MakeAvailable(lib-nlohmann)

add_subdirectory(uiutils)
