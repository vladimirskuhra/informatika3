

#include "config.hpp"
#include <fstream>
#include <stdexcept>

namespace turtlepreter {

Config Config::createDefault() {
    Config cfg;
   
    cfg.m_imageTurtle   = "turtlepreter/resources/turtle.png";
    cfg.m_imageRunner   = "turtlepreter/resources/runner.png";
    cfg.m_imageSwimmer  = "turtlepreter/resources/swimmer.png";
    cfg.m_imageTortoise = "turtlepreter/resources/tortoise.png";
    cfg.m_width  = 1280;
    cfg.m_height = 720;
    return cfg;
}

Config Config::createFromJsonNode(const nlohmann::json& node) {
    Config cfg;
    
    cfg.m_imageTurtle   = node.value("imageTurtle",   "turtlepreter/resources/turtle.png");
    cfg.m_imageRunner   = node.value("imageRunner",   "turtlepreter/resources/runner.png");
    cfg.m_imageSwimmer  = node.value("imageSwimmer",  "turtlepreter/resources/swimmer.png");
    cfg.m_imageTortoise = node.value("imageTortoise", "turtlepreter/resources/tortoise.png");
    cfg.m_width         = node.value("width",  1280);
    cfg.m_height        = node.value("height", 720);
    return cfg;
}

Config Config::createFromJsonFile(const std::filesystem::path& path) {
    std::ifstream ifst(path);
    if (!ifst.is_open()) {
        throw std::runtime_error("Failed to open: " + path.string());
    }
    const auto j = nlohmann::json::parse(ifst);
    return Config::createFromJsonNode(j);
}

Config Config::createFromArgs(int argc, const char* argv[]) {
    for (int i = 1; i + 1 < argc; ++i) {
        if (std::string(argv[i]) == "--config") {
            return createFromJsonFile(argv[i + 1]);
        }
    }
    return createDefault();
}

void Config::print(std::ostream& ost) const {
    ost << "Config:\n"
        << "  imageTurtle   = " << m_imageTurtle   << "\n"
        << "  imageRunner   = " << m_imageRunner   << "\n"
        << "  imageSwimmer  = " << m_imageSwimmer  << "\n"
        << "  imageTortoise = " << m_imageTortoise << "\n"
        << "  width         = " << m_width         << "\n"
        << "  height        = " << m_height        << "\n";
}

} // namespace turtlepreter
