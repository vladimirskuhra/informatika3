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



// PREŤAŽENIE OPERATOR<< PRE VÝPIS WeatherRecord
inline std::ostream &operator<<(std::ostream &ost, const weather::WeatherRecord &record) {
    // Výpis dátumu po jednotlivých zložkách (C++20 chrono)
    ost << record.city << " | "
        << record.date << " | "
        << record.tempMin << " / "
        << record.tempMax << " | "
        << record.temp0700 << " , "
        << record.temp1400 << " , "
        << record.temp2100 << " | "
        << record.elevation;
    return ost;
}

} // namespace weather

#endif