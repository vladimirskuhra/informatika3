#include "display_row.hpp"
#include <iostream>

namespace asciid {

DisplayRow::DisplayRow() : m_pixels(0) {}

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

bool DisplayRow::isPixelOn(int i) const {
    if (boundCheck(i)) {
        return (m_pixels & (1 << i)) != 0;
    }
    return false;
}

void DisplayRow::clearPixels() {
    m_pixels = 0;
}

void DisplayRow::print() const {
    for (int i = 0; i < getPixelCount(); ++i) {
        std::cout << (isPixelOn(i) ? "*" : " ");
    }
}

void DisplayRow::printLn() const {
    print();
    std::cout << std::endl;
}

} // namespace asciid