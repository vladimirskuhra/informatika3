#include "display_row.hpp"
#include <iostream>
int main() {
    asciid::DisplayRow *row = new asciid::DisplayRow();
    std::cout << row->getPixelCount() << "\n";
    delete row;
}