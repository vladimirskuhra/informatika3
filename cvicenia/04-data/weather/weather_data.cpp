#include "weather_data.hpp"
#include "uiutils/ui_utils.hpp"

namespace weather {
    WeatherLoader::WeatherLoader(df::CSVConfig config)
    : CSVLoader(std::move(config))
    {
    }

    WeatherRecord WeatherLoader::create(const csv::CSVRow &row) const
    {
        const std::string_view dateStr = row["datum"].get_sv();
        std::optional<std::chrono::year_month_day> dateOpt = uiutils::parseDate(dateStr);
        if(!dateOpt)
        {
            throw std::runtime_error("Invalid date format: " + std::string(dateStr));
        }
        WeatherRecord record;
        record.city = row["mesto"].get<std::string>();\
        record.tempMin = row["t_min"].get<float>();
        record.tempMax = row["t_max"].get<float>();
        record.temp0700 = row["t_0700"].get<float>();
        record.temp1400 = row["t_1400"].get<float>();
        record.temp2100 = row["t_2100"].get<float>();
        record.elevation = row["elevation"].get<int>();
        record.date = *dateOpt;

        return record;
    }

} // namespace weather
