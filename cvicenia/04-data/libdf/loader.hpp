#ifndef LIBDF_LOADER_HPP
#define LIBDF_LOADER_HPP

#include <filesystem>
#include "data_frame.hpp"

namespace df {
    template <typename T>
    class Loader { // toto bude abstraktna trieda (rozhranie/interface) pre nacitavanie dat do dataframu
        public:
            virtual ~Loader() = default; // virtualny destruktor pre spravne uvolnenie zdrojov pri dedeni
            virtual DataFrame<T> load(const std::filesystem::path &path) const = 0; // cista virtualna metoda na nacitanie dat zo suboru
    };
} // namespace df

#endif
