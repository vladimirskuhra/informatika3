#ifndef TURTLEPRETER_PERK_HPP
#define TURTLEPRETER_PERK_HPP

#include "controllable.hpp"
#include "interpreter.hpp"

namespace turtlepreter {


class Perk : virtual public Controllable {
public:
    Perk(const std::string& imgPath, float centerX, float centerY, int fullStat);
    bool hasStat() const;
    void useStat();
    void reset() override;
protected:
    int m_stat;
    int m_fullStat;
};




class Runner : public Perk {
public:
    Runner(const std::string& imgPath, float centerX, float centerY);
    bool hasStamina() const { return hasStat(); }
    void useStamina()       { useStat(); }
};

class Swimmer : public Perk {
public:
    Swimmer(const std::string& imgPath, float centerX, float centerY);
    bool hasOxygen() const { return hasStat(); }
    void useOxygen()       { useStat(); }
};




class CommandRun : public ICommand {
public:
    CommandRun(float x, float y);
    void execute(Controllable &c) override;
    bool canBeExecutedOn(Controllable &c) override;
    std::string toString() override;
private:
    float m_x, m_y;
};

class CommandSwim : public ICommand {
public:
    CommandSwim(float x, float y);
    void execute(Controllable &c) override;
    bool canBeExecutedOn(Controllable &c) override;
    std::string toString() override;
private:
    float m_x, m_y;
};


} // namespace turtlepreter
#endif