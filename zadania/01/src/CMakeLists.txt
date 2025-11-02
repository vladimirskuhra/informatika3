add_executable(main
    main.cpp
    set_visualizer.cpp
    terminal.cpp
    display.cpp
    display_row.cpp
)

target_compile_options(main PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -std=c++20
    -g
)