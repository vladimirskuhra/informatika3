
// config.hpp
#pragma once
#include <string>
#include <filesystem>
#include <ostream>
#include <nlohmann/json.hpp>

namespace turtlepreter {

class Config {
public:
    static Config createDefault();
    static Config createFromArgs(int argc, const char* argv[]);             // voliteľné
    static Config createFromJsonNode(const nlohmann::json& node);
    static Config createFromJsonFile(const std::filesystem::path& path);

    const std::string& getImageTurtle()   const { return m_imageTurtle; }
    const std::string& getImageRunner()   const { return m_imageRunner; }
    const std::string& getImageSwimmer()  const { return m_imageSwimmer; }
    const std::string& getImageTortoise() const { return m_imageTortoise; }
    int  getWidth()  const { return m_width; }
    int  getHeight() const { return m_height; }

    void print(std::ostream& ost) const;

private:
    Config() = default;

    std::string m_imageTurtle;
    std::string m_imageRunner;
    std::string m_imageSwimmer;
    std::string m_imageTortoise;
    int m_width  = 1280;
    int m_height = 720;
};

} // namespace turtlepreter
