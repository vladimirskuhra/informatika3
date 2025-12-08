#include "perk.hpp"
#include "heap_monitor.hpp"

namespace turtlepreter {

Perk::Perk(const std::string& imgPath, float cX, float cY, int fullStat)
    : Controllable(imgPath, cX, cY)
    , m_stat(fullStat)
    , m_fullStat(fullStat) {}

bool Perk::hasStat() const { return m_stat > 0; }
void  Perk::useStat()      { if (hasStat()) --m_stat; }

void Perk::reset() {
    Controllable::reset();
    m_stat = m_fullStat;
}


Runner::Runner(const std::string& i, float cX, float cY)
    : Controllable(i, cX, cY)
    , Perk(i, cX, cY, 5) {}

Swimmer::Swimmer(const std::string& i, float cX, float cY)
    : Controllable(i, cX, cY)
    , Perk(i, cX, cY, 10) {}


CommandRun::CommandRun(float x, float y) : m_x(x), m_y(y) {}

void CommandRun::execute(Controllable& c) {
    if (auto* r = dynamic_cast<Runner*>(&c)) {
        if (r->hasStamina()) {
            r->getTransformation().translation.setValue({m_x, m_y});
            r->useStamina();
        }
    }
}

bool CommandRun::canBeExecutedOn(Controllable& c) {
    return dynamic_cast<Runner*>(&c) != nullptr;
}

std::string CommandRun::toString() {
    return "Run " + std::to_string(m_x) + ", " + std::to_string(m_y);
}

CommandSwim::CommandSwim(float x, float y) : m_x(x), m_y(y) {}

void CommandSwim::execute(Controllable& c) {
    if (auto* s = dynamic_cast<Swimmer*>(&c)) {
        if (s->hasOxygen()) {
            s->getTransformation().translation.setValue({m_x, m_y});
            s->useOxygen();
        }
    }
}

bool CommandSwim::canBeExecutedOn(Controllable& c) {
    return dynamic_cast<Swimmer*>(&c) != nullptr;
}

std::string CommandSwim::toString() {
    return "Swim " + std::to_string(m_x) + ", " + std::to_string(m_y);
}

} // namespace turtlepreter