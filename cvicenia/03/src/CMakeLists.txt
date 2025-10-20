add_executable(main
    main.cpp
    game_of_life.cpp
    display.cpp
    display_row.cpp
    filters.cpp
    heap_monitor.cpp
    terminal.cpp
    ui_utils.cpp
)

target_compile_options(main PUBLIC
    -Wall
    -Wextra
    -Wpedantic
    -std=c++20
    -g
)