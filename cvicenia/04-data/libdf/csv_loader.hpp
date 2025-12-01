#ifndef LIBDF_CSV_LOADER_HPP
#define LIBDF_CSV_LOADER_HPP


#include <csv.hpp>
#include "loader.hpp"
#include "csv_config.hpp"
#include <filesystem>
#include <vector>

namespace df {
    template <typename T>
    class CSVLoader : public Loader<T> {
        public:
            CSVLoader(CSVConfig config);
            DataFrame<T> load(const std::filesystem::path &path) const override;
            virtual T create(const csv::CSVRow &row) const;
        private:
            CSVConfig m_config;
    };
    template <typename T>
    inline CSVLoader<T>::CSVLoader(CSVConfig config) 
    : m_config(std::move(config)){
    };
    template <typename T>
    inline DataFrame<T> CSVLoader<T>::load(const std::filesystem::path &path) const {
        csv::CSVFormat format;
        format.delimiter(m_config.getDelimiter());
        csv::CSVReader reader(path.string(), format);
        std::vector<T> result;
        result.reserve(reader.n_rows());
        for (const csv::CSVRow &row : reader) {
            result.push_back(this->create(row));
        }
        return DataFrame<T>(std::move(result));
    };

} // namespace df

#endif
