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
    turtle.jump(100, 100);
    turtle.rotate(3.14);
    // TODO
    /*VYTVARAME STROM S NODE-mi */
    tp::Node* n1 = new tp::Node(new tp::CommandMove(100));
    tp::Node* n2 = new tp::Node(new tp::CommandJump(200, 300));
    tp::Node* n3 = new tp::Node(new tp::CommandRotate(3.14));
    n1->addSubnode(n2);
    n1->addSubnode(n3);

    // Interpret the tree from the root.
    tp::Interpreter interpreter(n1);

    // Create GUI.
    tp::TurtleGUI turtleGUI(&turtle, &interpreter);

    // Render GUI.
    window->setGUI(&turtleGUI);
    window->run();

    delete n1;//staci zavolat delete na ten koren stromu, lebo destruktor Node sa postara o zbytok
    friimgui::Window::releaseWindow();
}
