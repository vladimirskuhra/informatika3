#ifndef UIUTILS_UI_UTILS_HPP
#define UIUTILS_UI_UTILS_HPP

#include <charconv>
#include <chrono>
#include <optional>

namespace uiutils {

/**
 * Prekonvertuje reťazec @p s reprezentujúci dátum vo formáte `YYYY-MM-DD`
 * na typ @c std::chrono::year_month_day
 * Pri nesprávnom formáte vráti @c std::nullopt
 */
std::optional<std::chrono::year_month_day> parseDate(std::string_view s);

/**
 * Prekonvertuje raťazec @p s reprezentujúci číslo na celočíselný typ @c T
 * Vráti číslo obalené v inštancii @c std::optional<T>
 * Ak @p s neobsahuje číslo vráti @c std::nullopt
 */
template<typename T>
std::optional<T> parseInt(std::string_view s) {
    T result;
    const char *first = s.data();
    const char *last = s.data() + s.size();
    const std::from_chars_result fcResult
        = std::from_chars(first, last, result);
    return fcResult.ec == std::errc() && fcResult.ptr == last
             ? std::optional<int>(result)
             : std::nullopt;
}

} // namespace uiutils

#endif
