#ifndef ASCIID_DISPLAY_HPP
#define ASCIID_DISPLAY_HPP

#include "display_row.hpp"

namespace asciid {

class Display {
public:
    Display(); //konstrkutor
    ~Display(); //destruktor
    /*
    destruktor - uvlonuje pamat, vola sa automaticky, 
        - zabranuje unikom pamate, 
        - vola sa pri konci programu alebo ked objekt zanika
    */
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
    static const int N_ROWS = 8;
    static const int N_COLS = 8;
private:
    /* prakticky rozdiel medzi DisplayRow* m_rows[N_ROWS] a DisplayRow *m_rows[N_ROWS] NIE JE 
     */
    DisplayRow* m_rows[N_ROWS];
    bool boundCheck(int row, int col) const;
};

} // namespace asciid

#endif