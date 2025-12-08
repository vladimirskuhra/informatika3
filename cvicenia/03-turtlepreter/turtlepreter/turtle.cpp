#include "turtle.hpp"
#include <imgui/imgui.h>
#include <cmath>
#include "heap_monitor.hpp"
#include <iostream>
#include <string>
#include <cstdint>

namespace turtlepreter {
Turtle::Turtle(const std::string &img, float cX, float cY)
    : Controllable(img, cX, cY) {
}


void Turtle::draw(const friimgui::Region &r) {
    Controllable::draw(r);

    ImDrawList *dl = ImGui::GetWindowDrawList();
    const ImVec2 p0 = r.getP0();

    for (const auto &s : m_segments) {
        const ImVec2 a = {s.a.x + p0.x, s.a.y + p0.y};
        const ImVec2 b = {s.b.x + p0.x, s.b.y + p0.y};
        dl->AddLine(a, b, s.color, 2.0f);
    }
}

void Turtle::reset() {
    Controllable::reset();
    m_segments.clear();
    m_currentColor = ImColor(0, 255, 0);
    //m_path.clear();
}

void Turtle::move(float d) {
    auto &t = getTransformation();
    const ImVec2 p = t.translation.getValueOrDef();
    const float a = t.rotation.getValueOrDef();

    const ImVec2 dest(p.x + d * cosf(a), p.y + d * sinf(a));
    m_segments.push_back({p, dest, m_currentColor});
    t.translation.setValue(dest);
}

void Turtle::jump(float x, float y) {
    auto &t = getTransformation();
    const ImVec2 p = t.translation.getValueOrDef();
    const ImVec2 dest{x, y};
    m_segments.push_back({p, dest, m_currentColor});
    t.translation.setValue(dest);
}

void Turtle::rotate(float a) {
    auto &tr = getTransformation();
    const float current = tr.rotation.getValueOrDef();
    tr.rotation.setValue(current + a);
}
size_t Turtle::getPathSegmentCount() const { 
    return m_segments.size(); }

ImVec4 Turtle::getPathSegmentPoints(size_t i) const {
    const auto& s = m_segments[i];
    return ImVec4(s.a.x, s.a.y, s.b.x, s.b.y);
}

ImColor Turtle::getPathSegmentColor(size_t i) const { return m_segments[i].color; }

void Turtle::setColor(ImColor color){
    m_currentColor = color;
};

Tortoise::Tortoise(const std::string &img, float cX, float cY)
    : Controllable(img, cX, cY),
      Turtle(img, cX, cY),
      Runner(img, cX, cY) {
}

void Tortoise::reset() {
    Turtle::reset();
    Runner::reset();
}

void TurtleCommand::execute(Controllable &c) {
    if (auto *t = dynamic_cast<Turtle *>(&c)) {
        this->log(std::cout); 
        executeOnTurtle(*t);
    } else {
        
    }
}

bool TurtleCommand::canBeExecutedOn(Controllable &c) {
    return dynamic_cast<Turtle *>(&c) != nullptr;
}

CommandMove::CommandMove(float d)
    : m_d(d) {
}

void CommandMove::executeOnTurtle(Turtle &t) {
    t.move(m_d);
}

std::string CommandMove::toString() {
    return "Move " + std::to_string(m_d);
}

void CommandMove::log(std::ostream &os) const
{
    os << "move(" << m_d << ")\n";
}

CommandJump::CommandJump(float x, float y)
    : m_x(x), m_y(y) {
}

void CommandJump::executeOnTurtle(Turtle &t) {
    t.jump(m_x, m_y);
}

std::string CommandJump::toString() {
    return "Jump " + std::to_string(m_x) + ", " + std::to_string(m_y);
}

void CommandJump::log(std::ostream &os) const
{
    os << "jump(" << m_x << ", " << m_y << ")\n";
}

CommandRotate::CommandRotate(float a)
    : m_a(a) {
}

void CommandRotate::executeOnTurtle(Turtle &t) {
    t.rotate(m_a);
}

std::string CommandRotate::toString() {
    return "Rotate " + std::to_string(m_a);
}
void CommandRotate::log(std::ostream &os) const
{
    os << "rotate(" << m_a << ")\n";
}

CommandSetColor::CommandSetColor(ImColor color)
    : m_color(color) {}

void CommandSetColor::executeOnTurtle(Turtle& t) {
    t.setColor(m_color);
}

std::string CommandSetColor::toString() {
    return "SetColor";
}

void CommandSetColor::log(std::ostream &os) const
{
    os << "setColor(" << m_color.Value.x << ", " << m_color.Value.y << ", " << m_color.Value.z << ", " << m_color.Value.w << ")\n";
}
} // namespace turtlepreter