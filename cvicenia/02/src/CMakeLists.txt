add_executable(asciid)

target_sources(asciid PUBLIC
    display_row.cpp
    main.cpp
)

target_compile_options(asciid PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -std=c++20
    -g
)