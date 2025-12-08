#ifndef TURTLEPRETER_TURTLE_GUI_HPP
#define TURTLEPRETER_TURTLE_GUI_HPP
#include <libfriimgui/window.hpp>
#include "interpreter.hpp"
#include "controllable.hpp"

namespace turtlepreter {
class TurtleGUI:public friimgui::GUIBuilder{
public:
    TurtleGUI(Controllable* c,Interpreter* i); 
    void build() override;
private:
    void buildTopBar();
    void buildLeftPanel();
    void buildSplitter();
    void buildRightPanel();
    void populateTreeNodes(Node* n);
    Controllable* m_controllable; 
    Interpreter* m_interpreter; 
    float m_widthLeftPanel;
};
} // namespace turtlepreter
#endif