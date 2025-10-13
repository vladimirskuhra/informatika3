#include "display.hpp"
#include <iostream>
#include "heap_monitor.hpp"

namespace asciid {

Display::Display() {
    for (int i = 0; i < N_ROWS; ++i) {
        m_rows[i] = new DisplayRow();
    }
}

Display::~Display() {
    for (int i = 0; i < N_ROWS; ++i) {
        delete m_rows[i];
    }
}

int Display::getRowCount() const {
    return N_ROWS;
}

int Display::getColCount() const {
    return N_COLS;
}

bool Display::boundCheck(int row, int col) const {
    return row >= 0 && row < N_ROWS && col >= 0 && col < N_COLS;
}

void Display::turnPixelOn(int row, int col) {
    if (boundCheck(row, col)) {
        m_rows[row]->turnPixelOn(col);
    }
}

void Display::turnPixelOff(int row, int col) {
    if (boundCheck(row, col)) {
        m_rows[row]->turnPixelOff(col);
    }
}

void Display::flipPixel(int row, int col) {
    if (boundCheck(row, col)) {
        m_rows[row]->flipPixel(col);
    }
}
/*
? - tzv. ternarny operator je skrateny zapis if-else,
mam napriklad a ? b : c; 
ak je podmienka a splnena, 
vykona/vrati b ak nie je splnena vykona/vrati c
*/
bool Display::isPixelOn(int row, int col) const {
    return boundCheck(row, col) ? m_rows[row]->isPixelOn(col) : false;
}

void Display::clearPixels() {
    for (int i = 0; i < N_ROWS; ++i) {
        m_rows[i]->clearPixels();
    }
}

Color Display::getPixelColor(int row, int col) const {
    return boundCheck(row, col) ? m_rows[row]->getPixelColor(col) : Color::White;
}

void Display::setPixelColor(int row, int col, Color c) {
    if (boundCheck(row, col)) {
        m_rows[row]->setPixelColor(col, c);
    }
}

void Display::print() const {
    for (int i = 0; i < N_ROWS; ++i) {
        m_rows[i]->printLn();
    }
}

void Display::printRowIn(int row) const {
    if (row >= 0 && row < N_ROWS) {
        m_rows[row]->printLn();
    }
}

} // namespace asciid