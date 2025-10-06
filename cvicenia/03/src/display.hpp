#ifndef ASCIID_DISPLAY_HPP
#define ASCIID_DISPLAY_HPP

#include "display_row.hpp"

namespace asciid {

class Display {
public:
    static const int N_ROWS = 8;
    static const int N_COLS = 8;
    Display();
    ~Display();

    int getRowCount() const;
    int getColCount() const;

    void turnPixelOn(int row, int col);
    void turnPixelOff(int row, int col);
    void flipPixel(int row, int col);
    bool isPixelOn(int row, int col) const;
    void clearPixels();

    Color getPixelColor(int row, int col) const;
    void setPixelColor(int row, int col, Color c);

    void print() const;
    void printRowIn(int row) const;

private:
    DisplayRow* m_rows[N_ROWS];
    bool boundCheck(int row, int col) const;
};

} // namespace asciid

#endif