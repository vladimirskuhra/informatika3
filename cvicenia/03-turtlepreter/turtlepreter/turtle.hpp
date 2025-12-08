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
    void rotate(float a);
    size_t getPathSegmentCount() const;
    ImVec4 getPathSegmentPoints(size_t i) const;
    ImColor getPathSegmentColor(size_t i) const;
    void setColor(ImColor color);

private:
    struct Segment
    {
        ImVec2 a;
        ImVec2 b;
        ImColor color;
    };
    std::vector<Segment> m_segments;
    ImColor m_currentColor{0, 255, 0};
    std::vector<ImVec4> m_path;
};


class Tortoise : public Turtle, public Runner {
public:
    Tortoise(const std::string& imgPath, float centerX, float centerY);
    void reset() override;
};


class TurtleCommand : public ICommand {
public:
    void execute(Controllable& c) override;          
    bool canBeExecutedOn(Controllable& c) override;            
    virtual void executeOnTurtle(Turtle& t) = 0;
    virtual std::string toString() override = 0;
    virtual void log(std::ostream &os) const override = 0;
};


class CommandMove : public TurtleCommand {
public:
    explicit CommandMove(float d);
    void executeOnTurtle(Turtle& t) override;
    std::string toString() override;
    virtual void log(std::ostream &os) const override;
private:
    float m_d;
};

class CommandJump : public TurtleCommand {
public:
    CommandJump(float x, float y);
    void executeOnTurtle(Turtle& t) override;
    std::string toString() override;
    virtual void log(std::ostream &os) const override;
private:
    float m_x, m_y;
};
class CommandRotate : public TurtleCommand {
public: CommandRotate(float a); 
void executeOnTurtle(Turtle &t) override; 
std::string toString() override; 
virtual void log(std::ostream &os) const override;
private: 
float m_a;
};

class CommandSetColor : public TurtleCommand {
public: 
    explicit CommandSetColor(ImColor color); 
    void executeOnTurtle(Turtle &t) override; 
    std::string toString() override;
    void log(std::ostream &os) const override;
private: 
    ImColor m_color;
};
} // namespace turtlepreter
#endif