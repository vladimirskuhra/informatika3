#include "display.hpp"
#include "terminal.hpp"
#include "filters.hpp"
#include <iostream>
#include "heap_monitor.hpp"

using namespace asciid;

int main() {
    Terminal::clear();
    Display d;
    d.turnPixelOn(0, 0); d.setPixelColor(0, 0, Color::Red);
    d.turnPixelOn(1, 1); d.setPixelColor(1, 1, Color::Green);
    d.turnPixelOn(2, 2); d.setPixelColor(2, 2, Color::Blue);
    std::cout << "Original:\n";
    d.print();

    filters::flip(&d);
    std::cout << "\nAfter flip:\n";
    d.print();

    filters::repaint(&d, Color::Red, Color::Magenta);
    std::cout << "\nAfter repaint Red->Magenta:\n";
    d.print();

    filters::transpose(&d);
    std::cout << "\nAfter transpose:\n";
    d.print();

    d.turnPixelOn(3, 3); d.setPixelColor(3, 3, Color::Yellow);
    filters::fill(&d, 3, 3, Color::Cyan);
    std::cout << "\nAfter fill at (3,3) with Cyan:\n";
    d.print();

    return 0;
}