#include "ui_utils.hpp"

namespace uiutils {

std::optional<std::chrono::year_month_day> parseDate(std::string_view s) {
    if (s.size() != 10) {
        return std::nullopt;
    }
    const std::string_view yStr = s.substr(0, 4);
    const std::string_view mStr = s.substr(5, 2);
    const std::string_view dStr = s.substr(8, 2);
    const std::optional<int> yOpt = parseInt<int>(yStr);
    const std::optional<unsigned> mOpt = parseInt<unsigned>(mStr);
    const std::optional<unsigned> dOpt = parseInt<unsigned>(dStr);
    if (! yOpt || ! mOpt || ! dOpt) {
        return std::nullopt;
    }
    return std::chrono::year_month_day(
        std::chrono::year {*yOpt},
        std::chrono::month {*mOpt},
        std::chrono::day {*dOpt}
    );
}

} // namespace uiutils
