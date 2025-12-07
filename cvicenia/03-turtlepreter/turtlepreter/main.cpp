
// main.cpp


#include "interpreter.hpp"
#include "turtle.hpp"
#include "turtle_gui.hpp"
#include "perk.hpp"
#include <libfriimgui/window.hpp>
#include <filesystem>
#include <iostream>
#include "config.hpp"          // všetky externé/systemové hlavičky pred týmto...
#include "heap_monitor.hpp"    // ...až ÚPLNE NA KONIEC



int main(int argc, const char* argv[]) {    // <- potrebuješ argc/argv v main
    namespace tp = turtlepreter;

    // 0) Konfigurácia – priama inicializácia
    tp::Config cfg = tp::Config::createFromArgs(argc, argv);
    // alebo
    // auto cfg = tp::Config::createFromArgs(argc, argv);

    cfg.print(std::cout);

    const int   cWidth   = cfg.getWidth();
    const int   cHeight  = cfg.getHeight();
    const float cCenterX = cWidth  / 2.0f;
    const float cCenterY = cHeight / 2.0f;

    friimgui::Window* window = friimgui::Window::initializeWindow(cWidth, cHeight);


    
    std::cout << "cwd = " << std::filesystem::current_path().string() << "\n";

    std::filesystem::path tortoiseP = cfg.getImageTortoise();
    std::filesystem::path runnerP   = cfg.getImageRunner();
    std::filesystem::path swimmerP  = cfg.getImageSwimmer();

    bool ok = true;
    if (!std::filesystem::exists(tortoiseP)) { std::cerr << "Asset missing: " << tortoiseP << "\n"; ok = false; }
    if (!std::filesystem::exists(runnerP))   { std::cerr << "Asset missing: " << runnerP   << "\n"; ok = false; }
    if (!std::filesystem::exists(swimmerP))  { std::cerr << "Asset missing: " << swimmerP  << "\n"; ok = false; }
    if (!ok) {
        friimgui::Window::releaseWindow();
        return 1;

    }
    
    tp::Tortoise tortoise(tortoiseP.string(), cCenterX,         cCenterY);
    tp::Runner   runner(  runnerP.string(),   cCenterX - 150.f, cCenterY);
    tp::Swimmer  swimmer( swimmerP.string(),  cCenterX + 150.f, cCenterY);

    tp::Node* root = tp::Node::createSequentialNode();
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandRotate(1.0f)));
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandMove(100.f)));
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandRun(cCenterX, cCenterY + 120.f)));
    root->addSubnode(tp::Node::createLeafNode(new tp::CommandSwim(cCenterX, cCenterY - 120.f)));

    tp::Interpreter interpreter(root);

    tp::TurtleGUI gui(&tortoise, &interpreter);
    window->setGUI(&gui);

    window->run();

    delete root;
    friimgui::Window::releaseWindow();
    return 0;
}
