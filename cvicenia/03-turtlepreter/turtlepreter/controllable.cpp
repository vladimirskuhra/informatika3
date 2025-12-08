
#include "controllable.hpp"
#include "heap_monitor.hpp"
#include <filesystem>
#include <stdexcept>

namespace turtlepreter {

Controllable::Controllable(const std::string &imgPath)
    : m_image(friimgui::Image::createImage(imgPath))  
{
    if (!std::filesystem::exists(imgPath)) {
        throw std::runtime_error("Asset neexistuje: " + imgPath);
    }
    m_transformation.translation.setValue({0.f, 0.f});
    m_transformation.rotation.setValue(0.f);
    m_initPos = {0.f, 0.f};
    m_initAngle = 0.f;
}

Controllable::Controllable(const std::string &imgPath, float centerX, float centerY)
    : m_image(friimgui::Image::createImage(imgPath))  
{
    if (!std::filesystem::exists(imgPath)) {
        throw std::runtime_error("Asset neexistuje: " + imgPath);
    }
    m_transformation.translation.setValue({centerX, centerY});
    m_transformation.rotation.setValue(0.f);
    m_initPos = {centerX, centerY};
    m_initAngle = 0.f;
}

void Controllable::draw(const friimgui::Region &region) {
    m_image.draw(region, m_transformation);
}

void Controllable::reset() {
    m_transformation.translation.setValue(m_initPos);
    m_transformation.rotation.setValue(m_initAngle);
}

friimgui::Transformation& Controllable::getTransformation() {
    return m_transformation;
}

} // namespace turtlepreter
