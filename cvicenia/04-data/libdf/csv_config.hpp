#ifndef LIBDF_CONFIG_HPP
#define LIBDF_CONFIG_HPP

#include <nlohmann/json.hpp>

#include <filesystem>
#include <iosfwd>

namespace df {

class CSVConfig {
public:
    static CSVConfig createFromJsonNode(const nlohmann::json &node);
    static CSVConfig createFromJsonFile(const std::filesystem::path &path);
    static CSVConfig createFromParams(char delimiter);
    static CSVConfig createDefault();

public:
    char getDelimiter() const;
    void print(std::ostream &ost) const;

private:
    CSVConfig() = default;

private:
    char m_delimiter;
};

} // namespace df

#endif
