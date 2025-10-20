#include "ui_utils.hpp"

#include <charconv>
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

namespace uiutils {

bool promptYesNo(const std::string &prompt) {
    while (true) {
        std::cout << prompt << " [y/n]: ";
        char c;
        std::cin >> c;
        if (c == 'y' || c == 'Y') return true;
        if (c == 'n' || c == 'N') return false;
        std::cout << "Zadajte prosím 'y' alebo 'n'." << std::endl;
    }
}

int chooseOption(
    const std::string &prompt,
    const std::vector<std::string> &options
) {
    while (true) {
        std::cout << prompt << std::endl;
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i << ": " << options[i] << std::endl;
        }
        std::cout << "Vyberte číslo možnosti: ";
        std::string input;
        std::cin >> input;
        auto opt = parseInt(input);
        if (opt && *opt >= 0 && *opt < static_cast<int>(options.size()))
            return *opt;
        std::cout << "Neplatná voľba, skúste znova." << std::endl;
    }
}

int readInt(const std::string &prompt) {
    while (true) {
        std::cout << prompt << ": ";
        std::string input;
        std::cin >> input;
        auto opt = parseInt(input);
        if (opt) return *opt;
        std::cout << "Neplatné číslo, skúste znova." << std::endl;
    }
}

std::optional<int> readIntOpt(const std::string &prompt, int maxTries) {
    throw std::logic_error("Not implemented yet!");
}

std::string readString(const std::string &prompt) {
    std::cout << prompt;
    std::string input;
    std::cin >> input;
    return input;
}

std::optional<int> parseInt(const std::string &s) {
    int result;

    const char *first = s.data();
    const char *last = s.data() + s.size();
    const std::from_chars_result fcResult
        = std::from_chars(first, last, result);

    return fcResult.ec == std::errc() && fcResult.ptr == last
             ? std::optional<int>(result)
             : std::nullopt;
}

} // namespace uiutils
