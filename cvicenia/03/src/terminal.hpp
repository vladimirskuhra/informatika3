#ifndef ASCIID_TERMINAL_HPP
#define ASCIID_TERMINAL_HPP

#include <cstdint>

/**
 * Namespace asciid obsahuje všetky základné typy a utility pre ASCII displej.
 */
namespace asciid {

/**
 * Enum class Color
 * Predstavuje základné farby pre terminál podľa ANSI kódov.
 */
enum class Color : std::int8_t {
    Black = 30,   ///< ANSI kód 30
    Red = 31,     ///< ANSI kód 31
    Green = 32,   ///< ANSI kód 32
    Yellow = 33,  ///< ANSI kód 33
    Blue = 34,    ///< ANSI kód 34
    Magenta = 35, ///< ANSI kód 35
    Cyan = 36,    ///< ANSI kód 36
    White = 37    ///< ANSI kód 37
};

/**
 * Trieda Terminal ponúka statické metódy pre manipuláciu s terminálom.
 */
class Terminal {
public:
    /// Vyčistí terminál.
    static void clear();

    /// Nastaví farbu textu podľa zadaného enumu Color.
    static void setTextColor(Color c);

    /// Resetuje farbu textu na predvolenú.
    static void resetTextColor();
};

} // namespace asciid

#endif