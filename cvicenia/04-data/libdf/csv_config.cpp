#include "csv_config.hpp"

#include <fstream>
#include <stdexcept>

namespace df {

CSVConfig CSVConfig::createFromJsonFile(const std::filesystem::path &path) {
    std::ifstream ifst(path);
    if (!ifst.is_open()) {
        throw std::runtime_error("Failed to open: " + path.string());
    }
    return CSVConfig::createFromJsonNode(nlohmann::json::parse(ifst));
}

CSVConfig CSVConfig::createFromJsonNode(const nlohmann::json &node) {
    CSVConfig cfg;
    cfg.m_delimiter = std::string(node["delimiter"])[0];
    return cfg;
}

CSVConfig CSVConfig::createFromParams(char delimiter) {
    CSVConfig cfg;
    cfg.m_delimiter = delimiter;
    return cfg;
}

CSVConfig CSVConfig::createDefault() {
    CSVConfig cfg;
    cfg.m_delimiter = ';';
    return cfg;
}

char CSVConfig::getDelimiter() const {
    return m_delimiter;
}

void CSVConfig::print(std::ostream &ost) const {
    ost << "Delimiter:\t" << m_delimiter << "\n";
}

} // namespace df
