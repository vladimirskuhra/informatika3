add_executable(weather)

set(CMAKE_CXX_STANDARD 20)

target_link_libraries(weather PRIVATE df uiutils)

target_sources(weather PRIVATE weather_data.cpp main.cpp)

target_compile_options(weather PRIVATE -Wall -Wextra -Wpedantic)

target_compile_options(weather PUBLIC -std=c++20)
add_executable(weather main.cpp weather_data.cpp)
target_link_libraries(weather PRIVATE df uiutils)
target_compile_options(weather PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(weather PUBLIC -std=c++20)