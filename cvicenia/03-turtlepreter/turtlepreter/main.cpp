#include "interpreter.hpp"
#include "turtle.hpp"
#include "turtle_gui.hpp"

#include <libfriimgui/window.hpp>

#include <imgui/imgui.h>

#include <string>

#include "heap_monitor.hpp"

int main(int argc, char *argv[]) {
    namespace tp = turtlepreter;

    (void)argc;
    (void)argv;

    const std::string cTurtleImg = ".\\turtlepreter\\resources\\turtle.png";
    const int cWidth = 1280;
    const int cHeight = 720;
    const int cCenterX = cWidth / 2;
    const int cCenterY = cHeight / 2;

    // Create window, make OpenGL available.
    friimgui::Window *window // dynamicky vytvorene okno
        = friimgui::Window::initializeWindow(cWidth, cHeight);

    // Create the turtle.
    tp::Turtle turtle(cTurtleImg, cCenterX, cCenterY); //Objekt je ulozeny na zasobniku, nie v halde
    // TODO
    /*VYTVARAME STROM S NODE-mi */
    
    tp::Node* root = tp::Node::createSequentialNode();

    
    tp::Node* nodeRotate = tp::Node::createLeafNode(new tp::CommandRotate(3.14f));
    tp::Node* nodeMove   = tp::Node::createLeafNode(new tp::CommandMove(100.f));
    tp::Node* nodeJump   = tp::Node::createLeafNode(new tp::CommandJump(400, 200));
    tp::Node* move2      = tp::Node::createLeafNode(new tp::CommandMove(120));

    
    root->addSubnode(nodeRotate);
    root->addSubnode(nodeMove);
    root->addSubnode(nodeJump);
    root->addSubnode(move2);

    
    tp::Interpreter interpreter(root);

    // Create GUI.
    tp::TurtleGUI turtleGUI(&turtle, &interpreter);

    // Render GUI.
    window->setGUI(&turtleGUI);
    window->run();

    delete root;//staci zavolat delete na ten koren stromu, lebo destruktor Node sa postara o zbytok
    friimgui::Window::releaseWindow();
}
