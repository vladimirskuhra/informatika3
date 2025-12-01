#include "weather_data.hpp"
#include "libdf/csv_config.hpp"
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Pre správnu diakritiku v termináli vo Windows
#endif

    std::filesystem::path csvFile = "../data/shmu-may-2025.csv"; // cesta k CSV (musíš mať súbor)
    auto config = df::CSVConfig::createDefault(); // Použi default (alebo cez JSON)

    weather::WeatherLoader loader(config);
    auto df = loader.load(csvFile);

    df.print(std::cout); // Vypíše všetky záznamy, každý na riadku

    return 0;
}