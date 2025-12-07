#include "turtle.hpp"
#include <imgui/imgui.h>
#include <cmath>
#include "heap_monitor.hpp"


namespace turtlepreter {
Turtle::Turtle(const std::string& img, float cX, float cY):Controllable(img, cX, cY){}


void Turtle::draw(const friimgui::Region &r) {
    // 1) Nakresli obrázok cez predka (friimgui aplikuje transformáciu na image)
    Controllable::draw(r);

    // 2) Nakresli cestu (čiary) v tom istom regiónovom offsete
    ImDrawList* dl = ImGui::GetWindowDrawList();

    // Ľavý horný roh kresliaceho regiónu (screen súradnice)
    const ImVec2 p0 = r.getP0();

    for (const auto& s : m_path) {
        // s = {x1, y1, x2, y2} v „kanvas“ súradniciach; posuň ich o p0 do screen súradníc
        const ImVec2 a = { s.x + p0.x, s.y + p0.y };
        const ImVec2 b = { s.z + p0.x, s.w + p0.y };
        dl->AddLine(a, b, ImColor(ImVec4(0, 1, 0, 1)), 2.0f);
    }
}

void Turtle::reset() { Controllable::reset(); m_path.clear(); }
void Turtle::move(float d) { auto& t=getTransformation(); auto p=t.translation.getValueOrDef(); float a=t.rotation.getValueOrDef(); ImVec2 dest(p.x+d*cosf(a),p.y+d*sinf(a)); m_path.push_back({p.x,p.y,dest.x,dest.y}); t.translation.setValue(dest); }
void Turtle::jump(float x,float y) { auto& t=getTransformation(); auto p=t.translation.getValueOrDef(); m_path.push_back({p.x,p.y,x,y}); t.translation.setValue({x,y});}

void Turtle::rotate(float a) {
    auto& tr = getTransformation();
    float current = tr.rotation.getValueOrDef();
    tr.rotation.setValue(current + a); // relatívne
}
Tortoise::Tortoise(const std::string& img,float cX,float cY):Controllable(img,cX,cY),Turtle(img,cX,cY),Runner(img,cX,cY){}
void Tortoise::reset(){ Turtle::reset(); Runner::reset(); }

void TurtleCommand::execute(Controllable& c) /*final*/ /*override*/ {
    if (auto* t = dynamic_cast<Turtle*>(&c)) {
        executeOnTurtle(*t);
    } else {
        // interpretér by mal prevolať canBeExecutedOn, ale aj tak je bezpečnejšie nič neházať
    }
}

bool TurtleCommand::canBeExecutedOn(Controllable& c) /*override*/ {
    return dynamic_cast<Turtle*>(&c) != nullptr;
}
CommandMove::CommandMove(float d):m_d(d){}
void CommandMove::executeOnTurtle(Turtle& t){t.move(m_d);}
std::string CommandMove::toString(){ return "Move "+std::to_string(m_d); }
CommandJump::CommandJump(float x,float y):m_x(x),m_y(y){}
void CommandJump::executeOnTurtle(Turtle& t){t.jump(m_x,m_y);}
std::string CommandJump::toString(){ return "Jump "+std::to_string(m_x)+", "+std::to_string(m_y); }
CommandRotate::CommandRotate(float a):m_a(a){}
void CommandRotate::executeOnTurtle(Turtle& t){t.rotate(m_a);}
std::string CommandRotate::toString(){ return "Rotate "+std::to_string(m_a); }
}