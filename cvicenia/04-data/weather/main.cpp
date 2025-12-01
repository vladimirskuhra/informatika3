#include "weather_data.hpp"
#include "libdf/csv_config.hpp"
#include "libdf/data_frame.hpp"
#include <iostream>
#include <filesystem>
#include <locale>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Nastaví konzolu na UTF-8
#endif
    std::setlocale(LC_ALL, "");

    std::filesystem::path csvFile = "../data/shmu-may-2025.csv";
    auto config = df::CSVConfig::createDefault();
    weather::WeatherLoader loader(config);
    auto df = loader.load(csvFile);

    // Úloha 1: Najchladnejší deň
    const auto* coldest = df.min([](const weather::WeatherRecord &r) { return r.tempMin; });
    if (coldest) {
        std::cout << "Najchladnejší deň: " << coldest->date << " " << coldest->city
                  << " Tmin=" << coldest->tempMin << std::endl;
    }

    // Úloha 2: Mrzlo celý deň
    auto freezingDays = df.filter([](const weather::WeatherRecord &r) { return r.tempMax < 0; });
    std::cout << "Dni s celodenným mrazom:" << std::endl;
    for (const auto* r : freezingDays) {
        std::cout << r->date << " " << r->city
                  << " Tmax=" << r->tempMax
                  << " Elev=" << r->elevation << std::endl;
    }

    // Úloha 3: Priemerná nadmorská výška
    float avgElevation = df.mean<float>([](const weather::WeatherRecord &r) { return r.elevation; });
    std::cout << "Priemerná nadmorská výška: " << avgElevation << " m" << std::endl;

    // Úloha 4: Najväčší teplotný rozdiel
    const weather::WeatherRecord* maxDiffRecord = nullptr;
    float maxDiff = -1;
    df.apply([&](const weather::WeatherRecord &r) {
        float diff = r.tempMax - r.tempMin;
        if (diff > maxDiff) {
            maxDiff = diff;
            maxDiffRecord = &r;
        }
    });
    if (maxDiffRecord) {
        std::cout << "Najväčší rozdiel: " << maxDiffRecord->date << " "
                  << maxDiffRecord->city
                  << " Tmin=" << maxDiffRecord->tempMin
                  << " Tmax=" << maxDiffRecord->tempMax
                  << " Δ=" << maxDiff << std::endl;
    }

    return 0;
}
