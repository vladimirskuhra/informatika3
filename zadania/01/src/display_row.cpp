#include "display_row.hpp"
#include <iostream>

namespace asciid {

DisplayRow::DisplayRow() : m_pixels(0) {
    for (int i = 0; i < getPixelCount(); ++i) {
        setPixelColorUnsafe(i, Color::White);
    }
}

int DisplayRow::getPixelCount() const {
    return 8;
}

bool DisplayRow::boundCheck(int i) const {
    return i >= 0 && i < getPixelCount();
}

void DisplayRow::turnPixelOn(int i) {
    if (boundCheck(i)) {
        m_pixels |= (1 << i);
    }
}

void DisplayRow::turnPixelOff(int i) {
    if (boundCheck(i)) {
        m_pixels &= ~(1 << i);
    }
}

void DisplayRow::flipPixel(int i) {
    if (boundCheck(i)) {
        m_pixels ^= (1 << i);
    }
}
/*
isPixelOn pomnocou bitovej operacie AND zisti, 
ze ci je dany pixel zapnuty(1) alebo je vypnuty(0)
na zaklade posledneho bitoveho cisla
*/
bool DisplayRow::isPixelOn(int i) const {
    return boundCheck(i) ? (m_pixels & (1 << i)) != 0 : false;
}

void DisplayRow::clearPixels() {
    m_pixels = 0;
}

Color DisplayRow::getPixelColor(int i) const {
    return boundCheck(i) ? getPixelColorUnsafe(i) : Color::White;
}

void DisplayRow::setPixelColor(int i, Color c) {
    if (boundCheck(i)) {
        setPixelColorUnsafe(i, c);
    }
}

void DisplayRow::print() const {
    for (int i = 0; i < getPixelCount(); ++i) {
        if (isPixelOn(i)) {
            Terminal::setTextColor(m_colors[i]);
            std::cout << "*";
            Terminal::resetTextColor();
        } else {
            Terminal::setTextColor(Color::White);
            std::cout << ".";
            Terminal::resetTextColor();
        }
    }
}

void DisplayRow::printLn() const {
    print();
    std::cout << std::endl;
}

Color DisplayRow::getPixelColorUnsafe(int i) const {
    return m_colors[i];
}

void DisplayRow::setPixelColorUnsafe(int i, Color c) {
    m_colors[i] = c;
}

} // namespace asciid