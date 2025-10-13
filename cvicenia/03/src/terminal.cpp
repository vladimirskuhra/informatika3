#include "terminal.hpp"
#include <iostream>

namespace asciid {

void Terminal::clear() {
    std::cout << "\033c";
}

void Terminal::setTextColor(Color c) {
    std::cout << "\033[" << static_cast<int>(c) << "m";
}

void Terminal::resetTextColor() {
    std::cout << "\033[0m";
}

} // namespace asciid