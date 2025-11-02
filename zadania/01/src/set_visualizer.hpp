#ifndef SET_VISUALIZER_HPP
#define SET_VISUALIZER_HPP

#include "terminal.hpp"
#include <cstdint>

namespace setvis {
    /*
    Trieda SetVisualizer sluzi na vizualizaciu mnozin reprezentovanych ako 64-bitove cele cisla.
    Kazdy bit v tomto cisle reprezentuje jeden prvok mnoziny - ak je bit nastaveny na 1, prisluchajuci prvok je sucastou mnoziny,
    inak nie je.
    Trieda poskytuje metody na vypocet zakladnych operacii s mnozinami (prienik, zjednotenie, rozdiel, doplnok)
    a na vizualizaciu tychto mnozin a vysledkov operacii pomocou ASCII grafiky v terminali.
    64-bitove cislo je zobrazené ako 8x8 mriezka, kde kazdy pixel reprezentuje jeden bit/mnozinovy prvok.
    Pixel je zobrazeny ako hviezdicka '*' ak je bit nastaveny na 1, inak ako bodka '.'.
    Pri vizualizacii vysledkov operacii su pixely, ktore patria do vyslednej mnoziny zvyraznene cervenou farbou,
    zatial co pixely patriace do povodnych mnozin su zobrazené bielou farbou.
    */
    class SetVisualizer {
    public:
        SetVisualizer();
        ~SetVisualizer() = default;
        std::uint64_t calcIntersection(std::uint64_t a, std::uint64_t b);
        std::uint64_t calcUnion(std::uint64_t a, std::uint64_t b);
        std::uint64_t calcDifference(std::uint64_t a, std::uint64_t b);
        std::uint64_t calcComplement(std::uint64_t a);

        void showIntersection(std::uint64_t a, std::uint64_t b);
        void showUnion(std::uint64_t a, std::uint64_t b);
        void showDifference(std::uint64_t a, std::uint64_t b);
        void showComplement(std::uint64_t a);
        
        void showGrid(std::uint64_t set);
    };
    
} //namespace setvis
#endif // SET_VISUALIZER_HPP