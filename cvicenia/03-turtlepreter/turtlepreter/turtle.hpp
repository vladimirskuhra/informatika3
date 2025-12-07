#ifndef TURTLEPRETER_TURTLE_HPP
#define TURTLEPRETER_TURTLE_HPP

#include "controllable.hpp"
#include "interpreter.hpp"
#include "perk.hpp"
#include <vector>

namespace turtlepreter {
    class ICommand;
    
class Turtle : virtual public Controllable {
public:
    Turtle(const std::string& imgPath, float centerX, float centerY);
    void draw(const friimgui::Region& region) override;
    void reset() override;
    void move(float d);
    void jump(float x, float y);
    void rotate(float a); // zváž relatívne otáčanie
private:
    std::vector<ImVec4> m_path;
};


class Tortoise : public Turtle, public Runner {
public:
    Tortoise(const std::string& imgPath, float centerX, float centerY);
    void reset() override;
};


class TurtleCommand : public ICommand {
public:
    void execute(Controllable& c) /*final*/ override;          // pridaj override/final
    bool canBeExecutedOn(Controllable& c) override;            // názov podľa tvojho ICommand
    virtual void executeOnTurtle(Turtle& t) = 0;
};


class CommandMove : public TurtleCommand {
public:
    explicit CommandMove(float d);
    void executeOnTurtle(Turtle& t) override;
    std::string toString() override;
private:
    float m_d;
};

class CommandJump : public TurtleCommand {
public:
    CommandJump(float x, float y);
    void executeOnTurtle(Turtle& t) override;
    std::string toString() override;
private:
    float m_x, m_y;
};
class CommandRotate : public TurtleCommand {
public: CommandRotate(float a); void executeOnTurtle(Turtle &t) override; std::string toString() override; private: float m_a;
};
}
#endif