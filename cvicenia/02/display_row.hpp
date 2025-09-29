#ifndef ASCIID_DISPLAY_ROW_HPP
#define ASCIID_DISPLAY_ROW_HPP

#include <cstdint>

namespace asciid 
{
    class DisplayRow
    {
    private:
        /*data*/
        uint8_t m_pixels;
    public:
        //konstruktor
        DisplayRow();
        //getter
        std::uint8_t getPixelCount();
        //int getPixelCount() const; // int je typ premennej ktory ma 4 Bajty
        void turnPixelOn(int i);

        //destruktor
        ~DisplayRow();
    };
}
#endif
