#ifndef ASCIID_UI_UTILS_HPP
#define ASCIID_UI_UTILS_HPP

#include <optional>
#include <string>
#include <vector>

namespace uiutils {

/**
 * Vypíše @p prompt a načíta znak 'y' alebo 'n' reprezentujúci
 * hodnoty true a false.
 * Proces opakuje až pokým používateľ nezadá správny znak.
 */
bool promptYesNo(const std::string &prompt);

/**
 * Vypíše @p prompt a očíslované možnosti uvedené v parametri @p options
 * Od používateľa načíta číslo možnosti, ktoré potom vráti.
 * Proces opakuje až pokým používateľ nezadá správne číslo možnosti.
 */
int chooseOption(
    const std::string &prompt,
    const std::vector<std::string> &options
);

/**
 * Vypíše @p prompt a očíslované možnosti uvedené v parametri @p options
 * Od používateľa načíta číslo možnosti, ktoré potom vráti
 * obalené v inštancii @c std::optional<int>
 * Proces opakuje až pokým používateľ nezadá správne číslo možnosti.
 * Ak ani po @p maxTries nezadá používateľ správne číslo, vráti @c std::nullopt
 */
std::optional<int> chooseOptionOpt(
    const std::string &prompt,
    const std::vector<std::string> &options,
    int maxTries
);

/**
 * Vypíše @p prompt a načíta od používateľa reťazec reprezentujúci číslo.
 * Reťazec prekonvertuje na @c int metódou @c parseInt
 * Vráti načítané číslo.
 * Proces opakuje, až kým používateľ nezadá správny vstup.
 */
int readInt(const std::string &prompt);

/**
 * Vypíše @p prompt a načíta od používateľa reťazec reprezentujúci číslo.
 * Reťazec prekonvertuje na @c int metódou @c parseInt
 * Vráti načítané číslo obalené v inštancii @c std::optional<int>
 * Ak ani po @p maxTries nezadá používateľ správne číslo, vráti @c std::nullopt
 */
std::optional<int> readIntOpt(const std::string &prompt, int maxTries);

/**
 * Vypiše @p prompt a načíta od používateľa reťaze, ktorý vráti.
 */
std::string readString(const std::string &prompt);

/**
 * Prekonvertuje raťazec @p s reprezentujúci číslo na @c int
 * Vráti číslo obalené v inštancii @c std::optional<int>
 * Ak @p s neobsahuje číslo vráti @c std::nullopt
 */
std::optional<int> parseInt(const std::string &s);

} // namespace uiutils

#endif
