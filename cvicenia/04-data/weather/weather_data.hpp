#ifndef WEATHER_WEATHER_DATA_HPP
#define WEATHER_WEATHER_DATA_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include <iostream>
#include "libdf/csv_loader.hpp"

namespace weather {
    struct WeatherRecord {
        std::string city;
        std::chrono::year_month_day date;
        float tempMin;
        float tempMax;
        float temp0700;
        float temp1400;
        float temp2100;
        int elevation;
    };

    class WeatherLoader : public df::CSVLoader<WeatherRecord> {
    public:
        WeatherLoader(df::CSVConfig config);
        virtual WeatherRecord create(const csv::CSVRow &row) const override;
    };

} // namespace weather

// PREŤAŽENIE OPERATOR<< PRE VÝPIS WeatherRecord
inline std::ostream &operator<<(std::ostream &ost, const weather::WeatherRecord &record) {
    // Ak chceš formátovať dátum bez std::format z C++20, daj takto:
    std::chrono::year_month_day d = record.date;
    ost << record.city << " "
        << static_cast<int>(d.year()) << "-"
        << (unsigned(d.month()) < 10 ? "0" : "") << unsigned(d.month()) << "-"
        << (unsigned(d.day()) < 10 ? "0" : "") << unsigned(d.day()) << " "
        << record.tempMin << " "
        << record.tempMax << " "
        << record.temp0700 << " "
        << record.temp1400 << " "
        << record.temp2100 << " "
        << record.elevation;
    return ost;
}

#endif