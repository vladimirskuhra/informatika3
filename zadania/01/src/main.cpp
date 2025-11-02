#include "set_visualizer.hpp"
#include <cstdint>
#include <iostream>

int main() {
    setvis::SetVisualizer visualizer;

    const std::uint64_t a = 0x0F0F0F0F0F0F0F0F;
    const std::uint64_t b = 0xFFFFFFFF00000000;

    std::cout << "Mnozina A:\n";
    visualizer.showGrid(a);

    std::cout << "\nMnozina B:\n";
    visualizer.showGrid(b);

    visualizer.showIntersection(a, b);
    visualizer.showUnion(a, b);
    visualizer.showDifference(a, b);
    visualizer.showComplement(a);
    return 0;
}