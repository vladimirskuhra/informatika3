#include "set_visualizer.hpp"
#include "display.hpp"
#include <iostream>

namespace setvis {

    SetVisualizer::SetVisualizer() {}

    std::uint64_t SetVisualizer::calcIntersection(std::uint64_t a, std::uint64_t b) {
        return a & b;
    }

    std::uint64_t SetVisualizer::calcUnion(std::uint64_t a, std::uint64_t b) {
        return a | b;
    }

    std::uint64_t SetVisualizer::calcDifference(std::uint64_t a, std::uint64_t b) {
        return a & ~b;
    }

    std::uint64_t SetVisualizer::calcComplement(std::uint64_t a) {
        return ~a;
    }

    void SetVisualizer::showGrid(std::uint64_t set) { // pomocna metoda na zobrazenie mnoziny - musi byt verejna lebo ju volame v maine
        asciid::Display grid;
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                int bit = row * 8 + col;
                if (set & (1ULL << bit)) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::White);
                } else {
                    grid.turnPixelOff(row, col);
                }
            }
        }
        grid.print();
    }

    void SetVisualizer::showIntersection(std::uint64_t a, std::uint64_t b) {
        std::uint64_t result = calcIntersection(a, b);
        asciid::Display grid;
        for (int row = 0; row < grid.getRowCount(); ++row) {
            for (int col = 0; col < grid.getColCount(); ++col) {
                int bit = row * 8 + col;
                bool inA = a & (1ULL << bit);
                bool inB = b & (1ULL << bit);
                bool inResult = result & (1ULL << bit);

                if (inResult) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::Red);
                    // vysledok danej operacie, nastavime na cervenu hviezdicku
                } else if (inA || inB) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::White);
                    // povodne mnoziny "a" a "b" - zapneme pixel bielou hviezdickou
                } else {
                    grid.turnPixelOff(row, col); 
                    /* nepatri do prieniku a ani do jednej mnoziny - vypneme pixel
                    - upravena metoda print() v triede DisplayRow - teda DisplayRow::print()
                    */ 
                }
            }
        }
        std::cout << "intersection(a, b):\n";
        grid.print();
    }

    void SetVisualizer::showUnion(std::uint64_t a, std::uint64_t b) {
        std::uint64_t result = calcUnion(a, b);
        asciid::Display grid;
        for (int row = 0; row < grid.getRowCount(); ++row) {
            for (int col = 0; col < grid.getColCount(); ++col) {
                int bit = row * 8 + col; // tymto sposobom mapujeme bity do mriežky 8x8 kde su oznacene bity od 0 do 63 :) - nadhera
                bool inA = a & (1ULL << bit); // 1ULL - unsigned long long literal / aby sme mali istotu ze posuvame bit v 64-bitovom cisle
                bool inB = b & (1ULL << bit);
                bool inResult = result & (1ULL << bit); // zisti ci je bit na danej pozicii v podmnozine result nastaveny na 1

                if (inResult) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::Red);
                } else if (inA || inB) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::White);
                } else {
                    grid.turnPixelOff(row, col);
                }
            }
        }
        std::cout << "union(a, b):\n";
        grid.print();
    }

    void SetVisualizer::showDifference(std::uint64_t a, std::uint64_t b) {
        std::uint64_t result = calcDifference(a, b);
        asciid::Display grid;
        for (int row = 0; row < grid.getRowCount(); ++row) { // treida Display ma uchovane hodnoty N_ROWS a N_COLS odkial vieme ziskat pocet riadkov a stlpcov
            for (int col = 0; col < grid.getColCount(); ++col) {
                int bit = row * 8 + col;
                bool inA = a & (1ULL << bit);
                bool inResult = result & (1ULL << bit);

                if (inResult) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::Red);
                } else if (inA) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::White);
                } else {
                    grid.turnPixelOff(row, col);
                }
            }
        }
        std::cout << "difference(a, b):\n";
        grid.print();
    }

    void SetVisualizer::showComplement(std::uint64_t a) {
        std::uint64_t result = calcComplement(a);
        asciid::Display grid;
        for (int row = 0; row < grid.getRowCount(); ++row) {
            for (int col = 0; col < grid.getColCount(); ++col) {
                int bit = row * 8 + col;
                bool inA = a & (1ULL << bit);
                bool inResult = result & (1ULL << bit);

                if (inResult) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::Red);
                } else if (inA) {
                    grid.turnPixelOn(row, col);
                    grid.setPixelColor(row, col, asciid::Color::White);
                } else {
                    grid.turnPixelOff(row, col);
                }
            }
        }
        std::cout << "complement(a):\n";
        grid.print();
    }

} //namespace setvis