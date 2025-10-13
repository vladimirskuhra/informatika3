#ifndef ASCIID_DISPLAY_ROW_HPP
#define ASCIID_DISPLAY_ROW_HPP

#include <cstdint>
#include "terminal.hpp"

namespace asciid {

/**
 * Reprezentuje jeden riadok displeja s podporou farieb na každý pixel.
 */
class DisplayRow {
public:
    /**
     * Vytvorí riadok s vypnutými pixelmi a bielou farbou.
     */
    DisplayRow();

    /**
     * Počet pixelov v riadku.
     * @return Vždy 8.
     */
    int getPixelCount() const;

    /**
     * Zapne pixel na pozícii i (ak je index platný).
     */
    void turnPixelOn(int i);

    /**
     * Vypne pixel na pozícii i (ak je index platný).
     */
    void turnPixelOff(int i);

    /**
     * Preklopí pixel na pozícii i (ak je index platný).
     */
    void flipPixel(int i);

    /**
     * Zistí, či je pixel na pozícii i zapnutý.
     */
    bool isPixelOn(int i) const;

    /**
     * Vypne všetky pixely.
     */
    void clearPixels();

    /**
     * Získa farbu pixelu na pozícii i, kontroluje hranice.
     */
    Color getPixelColor(int i) const;

    /**
     * Nastaví farbu pixelu na pozícii i, kontroluje hranice.
     */
    void setPixelColor(int i, Color c);

    /**
     * Vypíše riadok na terminál s farbami.
     */
    void print() const;

    /**
     * Vypíše riadok na terminál s farbami a odriadkuje.
     */
    void printLn() const;

private:
    std::uint8_t m_pixels;
    Color m_colors[8];

    /**
     * Skontroluje, či je index v platnom rozsahu (0-7).
     */
    bool boundCheck(int i) const;

    /**
     * Získa farbu pixelu bez kontroly indexu (unsafe).
     */
    Color getPixelColorUnsafe(int i) const;

    /**
     * Nastaví farbu pixelu bez kontroly indexu (unsafe).
     */
    void setPixelColorUnsafe(int i, Color c);
};

} // namespace asciid

#endif