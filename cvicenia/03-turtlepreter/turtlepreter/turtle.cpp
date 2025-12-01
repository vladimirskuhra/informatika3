#include "turtle.hpp"

#include <imgui/imgui.h>

#include <cmath>

#include <stdexcept>
#include <cmath>

namespace turtlepreter {

Turtle::Turtle(const std::string &imgPath) :
    m_transformation(),
    m_image(friimgui::Image::createImage(imgPath)) 
{
    m_initPos = m_transformation.translation.getValueOrDef();
    m_initAngle = m_transformation.rotation.getValueOrDef();
}

Turtle::Turtle(const std::string &imgPath, float centerX, float centerY) :
    Turtle(imgPath) 
{
    const ImVec2 center(centerX, centerY);
    m_transformation.translation.setValue(center);
    m_initPos = center;
    m_initAngle = 0.f;
}

void Turtle::draw(const friimgui::Region &region) {
    const float thickness = 2.0f;
    const ImColor color = ImColor(ImVec4({0, 1, 0, 1}));
    ImDrawList *drawList = ImGui::GetWindowDrawList();

    for (const auto &segment : m_path) {
        const ImVec2 p0(segment.x, segment.y);
        const ImVec2 p1(segment.z, segment.w);
        drawList->AddLine(p0, p1, color, thickness);
    }
    m_image.draw(region, m_transformation);
}

void Turtle::reset() {
    m_path.clear();
    m_transformation.translation.setValue(m_initPos);
    m_transformation.rotation.setValue(m_initAngle);
}

void Turtle::move(float distance) {
    // Získaj aktuálnu pozíciu
    const ImVec2 pos = m_transformation.translation.getValueOrDef();
    // Získaj aktuálny uhol natočenia (v radiánoch)
    float angle = m_transformation.rotation.getValueOrDef();
    // Vypočítaj novú pozíciu
    float dx = distance * cosf(angle);
    float dy = distance * sinf(angle);
    ImVec2 dest(pos.x + dx, pos.y + dy);

    m_path.push_back(ImVec4(pos.x, pos.y, dest.x, dest.y));
    // Aktualizuj pozíciu
    m_transformation.translation.setValue(dest);
}

void Turtle::jump(float x, float y) {
    const ImVec2 pos = m_transformation.translation.getValueOrDef();
    const ImVec2 dest(x, y);
    m_path.push_back(ImVec4(pos.x, pos.y, dest.x, dest.y));
    m_transformation.translation.setValue(dest);
}

void Turtle::rotate(float angleRad) {
    // Set absolute rotation (in radians) for the turtle image.
    // The drawing code (friimgui::Image::draw) will use this value
    // when rotating the image region.
    m_transformation.rotation.setValue(angleRad);
}

} // namespace turtlepreter
