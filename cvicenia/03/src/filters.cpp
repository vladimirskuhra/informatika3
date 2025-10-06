#include "filters.hpp"
#include <queue>
#include "heap_monitor.hpp"

namespace asciid {
namespace filters {

void flip(Display* d) {
    for (int row = 0; row < d->getRowCount(); ++row) { // pozriet ako funguje lambda v c++
        for (int col = 0; col < d->getColCount(); ++col) {
            d->flipPixel(row, col);
        }
    }
}

void repaint(Display* d, Color from, Color to) {
    for (int row = 0; row < d->getRowCount(); ++row) {
        for (int col = 0; col < d->getColCount(); ++col) {
            if (d->getPixelColor(row, col) == from) {
                d->setPixelColor(row, col, to);
            }
        }
    }
}

void transpose(Display* d) {
    Display temp;
    for (int row = 0; row < d->getRowCount(); ++row) {
        for (int col = 0; col < d->getColCount(); ++col) {
            if (d->isPixelOn(row, col)) {
                temp.turnPixelOn(col, row);
                temp.setPixelColor(col, row, d->getPixelColor(row, col));
            } else {
                temp.turnPixelOff(col, row);
            }
        }
    }
    for (int row = 0; row < d->getRowCount(); ++row) {
        for (int col = 0; col < d->getColCount(); ++col) {
            if (temp.isPixelOn(row, col))
                d->turnPixelOn(row, col);
            else
                d->turnPixelOff(row, col);
            d->setPixelColor(row, col, temp.getPixelColor(row, col));
        }
    }
}

void fill(Display* d, int row, int col, Color c) {
    if (!d->isPixelOn(row, col)) return;
    Color original = d->getPixelColor(row, col);
    if (original == c) return;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    std::queue<std::pair<int, int>> q;
    q.push({row, col});

    while (!q.empty()) {
        auto [r, c0] = q.front();
        q.pop();
        if (!d->isPixelOn(r, c0)) continue;
        if (d->getPixelColor(r, c0) != original) continue;
        d->setPixelColor(r, c0, c);

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c0 + dc[i];
            if (nr >= 0 && nr < d->getRowCount() && nc >= 0 && nc < d->getColCount()) {
                q.push({nr, nc});
            }
        }
    }
}

} // namespace filters
} // namespace asciid