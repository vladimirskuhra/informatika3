#include "display_row.hpp"
#include <iostream>

int main() {
    asciid::DisplayRow row;
    row.turnPixelOn(0);
    row.turnPixelOn(1);
    row.turnPixelOn(2);
    row.printLn(); // Výstup: ***
    row.flipPixel(1);
    row.printLn(); // Výstup: * *
    row.clearPixels();
    row.printLn(); // Výstup:        
    std::cout << "Pixels: " << row.getPixelCount() << std::endl;
    return 0;
}