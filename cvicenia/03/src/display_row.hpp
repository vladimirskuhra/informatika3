#ifndef ASCIID_DISPLAY_ROW_HPP
#define ASCIID_DISPLAY_ROW_HPP

#include <cstdint>
#include "terminal.hpp"

namespace asciid {

class DisplayRow {
public:
    DisplayRow();
    int getPixelCount() const;
    void turnPixelOn(int i);
    void turnPixelOff(int i);
    void flipPixel(int i);
    bool isPixelOn(int i) const;
    void clearPixels();
    Color getPixelColor(int i) const;
    void setPixelColor(int i, Color c);
    void print() const;
    void printLn() const;
private:
    std::uint8_t m_pixels;
    Color m_colors[8];
    bool boundCheck(int i) const;
};

} // namespace asciid

#endif