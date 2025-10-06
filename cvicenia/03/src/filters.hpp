#ifndef ASCIID_FILTERS_HPP
#define ASCIID_FILTERS_HPP

#include "display.hpp"

namespace asciid {
namespace filters {

void flip(Display* d);
void repaint(Display* d, Color from, Color to);
void transpose(Display* d);
void fill(Display* d, int row, int col, Color c);

} // namespace filters
} // namespace asciid

#endif