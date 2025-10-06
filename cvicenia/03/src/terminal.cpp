#include "terminal.hpp"
#include <iostream>

namespace asciid {

void Terminal::clear() {
    std::cout << "\033c";
}

void Terminal::setTextColor(Color c) {
    int code = 30 + static_cast<int>(c);
    std::cout << "\033[" << code << "m";
}

void Terminal::resetTextColor() {
    std::cout << "\033[0m";
}

} // namespace asciid