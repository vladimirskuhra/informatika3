#include "turtle.hpp"

#include <imgui/imgui.h>

#include <cmath>

#include <stdexcept>
#include <cmath>

namespace turtlepreter {

Turtle::Turtle(const std::string &imgPath) :
    m_transformation(),
    m_image(friimgui::Image::createImage(imgPath)) {
}

Turtle::Turtle(const std::string &imgPath, float centerX, float centerY) :
    Turtle(imgPath) {
    m_transformation.translation.setValue({centerX, centerY});
}

void Turtle::draw(const friimgui::Region &region) {
    const float thickness = 1;
    const ImColor color = ImColor(ImVec4({0, 1, 0, 1}));
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    const ImVec2 p0 = region.getP0();
    // TODO
    (void)thickness;
    (void)color;
    (void)drawList;
    (void)p0;
    // TODO
    m_image.draw(region, m_transformation);
}

void Turtle::reset() {
    throw std::logic_error("Not implemented yet!");
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
    // Pridaj segment do cesty
    const ImVec4 segment(pos.x, pos.y, dest.x, dest.y);
    m_path.push_back(segment);
    // Aktualizuj pozíciu
    m_transformation.translation.setValue(dest);
}

void Turtle::jump(float x, float y) {
    const ImVec2 pos = m_transformation.translation.getValueOrDef();
    const ImVec2 dest(x, y);
    const ImVec4 segment(pos.x, pos.y, dest.x, dest.y);
    m_path.push_back(segment);
    m_transformation.translation.setValue(dest);
}

void Turtle::rotate(float angleRad) {
    // Set absolute rotation (in radians) for the turtle image.
    // The drawing code (friimgui::Image::draw) will use this value
    // when rotating the image region.
    m_transformation.rotation.setValue(angleRad);
}

} // namespace turtlepreter
