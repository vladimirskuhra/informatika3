#ifndef WEATHER_WEATHER_DATA_HPP
#define WEATHER_WEATHER_DATA_HPP

#include <string>
#include <cstdint>
#include <chrono>
#include "libdf/csv_loader.hpp"

namespace weather {
    struct WeatherRecord {
        std::string city;
        std::chrono::year_month_day date; //ukazuje ze je to zle ale ninja nepovie ani makke f
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
        virtual WeatherRecord create(const csv::CSVRow &row) const override; //virtual tu mozem pisat ale nemusim
    };

} // namespace weather

#endif
