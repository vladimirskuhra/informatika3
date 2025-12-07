
// main.cpp
#include "interpreter.hpp"
#include "turtle.hpp"
#include "turtle_gui.hpp"
#include "perk.hpp"
#include <libfriimgui/window.hpp>
#include <filesystem>
#include <iostream>
#include "heap_monitor.hpp"

int main() {
    namespace tp = turtlepreter;

    const int   cWidth   = 1280;
    const int   cHeight  = 720;
    const float cCenterX = cWidth  / 2.0f;
    const float cCenterY = cHeight / 2.0f;

    // 1) Inicializácia okna / backendu (pred obrázkami!)
    friimgui::Window* window = friimgui::Window::initializeWindow(cWidth, cHeight);

    // 2) Working directory + cesty k assetom
    std::cout << "cwd = " << std::filesystem::current_path().string() << "\n";

    
    std::filesystem::path tortoiseP = std::filesystem::path("../resources/tortoise.png");
    std::filesystem::path runnerP   = std::filesystem::path("../resources/runner.png");
    std::filesystem::path swimmerP  = std::filesystem::path("../resources/swimmer.png");


    bool ok = true;
    if (!std::filesystem::exists(tortoiseP)) { std::cerr << "Asset missing: " << tortoiseP << "\n"; ok = false; }
    if (!std::filesystem::exists(runnerP))   { std::cerr << "Asset missing: " << runnerP   << "\n"; ok = false; }
    if (!std::filesystem::exists(swimmerP))  { std::cerr << "Asset missing: " << swimmerP  << "\n"; ok = false; }
    if (!ok) {
        friimgui::Window::releaseWindow();
        return 1;
    }

    // 3) Entitiy – teraz je backend pripravený
    tp::Tortoise tortoise(tortoiseP.string(), cCenterX,        cCenterY);
    tp::Runner   runner(  runnerP.string(),   cCenterX - 150.f, cCenterY);
    tp::Swimmer  swimmer( swimmerP.string(),  cCenterX + 150.f, cCenterY);

    // 4) Strom príkazov
    tp::Node* root = tp::Node::createSequentialNode();
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandRotate(1.0f)));                    // TurtleCommand
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandMove(100.f)));                    // TurtleCommand
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandRun(cCenterX, cCenterY + 120.f)));   // Runner
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandSwim(cCenterX, cCenterY - 120.f)));  // Swimmer

    tp::Interpreter interpreter(root);

    // 5) GUI – demo nad Tortoise (ak chceš prepínať, dorob tlačidlá v GUI)
    tp::TurtleGUI gui(&tortoise, &interpreter);
    window->setGUI(&gui);

    // 6) Run loop
    window->run();

    // 7) Cleanup
    delete root;
    friimgui::Window::releaseWindow();
    return 0;
}
