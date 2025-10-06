#ifndef ASCIID_DISPLAY_ROW_HPP
#define ASCIID_DISPLAY_ROW_HPP

#include <cstdint>

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
    void print() const;
    void printLn() const;
private:
    std::uint8_t m_pixels;
    bool boundCheck(int i) const;
};

} // namespace asciid

#endif