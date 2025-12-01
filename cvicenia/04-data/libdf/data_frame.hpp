
#ifndef LIBDF_DATAFRAME_HPP
#define LIBDF_DATAFRAME_HPP

#include <vector>
#include <iostream>

namespace df {

    template<typename T>
    class DataFrame {
    public:
        explicit DataFrame(std::vector<T> data);
        void print(std::ostream &ost) const;
        size_t size() const;

        // Generické metódy
        template<typename Extractor>
        const T* min(Extractor extract) const;

        template<typename Extractor>
        const T* max(Extractor extract) const;

        template<typename Predicate>
        std::vector<const T*> filter(Predicate satisfies) const;

        template<typename ValueType, typename Extractor>
        ValueType mean(Extractor extract) const;

        template<typename F>
        void apply(F f) const;

    private:
        std::vector<T> m_data;
    };

    // Implementácia konštruktora
    template<typename T>
    inline DataFrame<T>::DataFrame(std::vector<T> data)
        : m_data(std::move(data)) {}

    // Výpis všetkých záznamov
    template<typename T>
    void DataFrame<T>::print(std::ostream &ost) const {
        for (const auto &item : m_data)
            ost << item << "\
";
    }

    // Veľkosť dát
    template<typename T>
    inline size_t DataFrame<T>::size() const {
        return m_data.size();
    }

    // MIN
    template<typename T>
    template<typename Extractor>
    const T* DataFrame<T>::min(Extractor extract) const {
        if (m_data.empty()) return nullptr;
        const T* result = &m_data.front();
        auto minValue = extract(*result);
        for (const auto &elem : m_data) {
            auto value = extract(elem);
            if (value < minValue) {
                minValue = value;
                result = &elem;
            }
        }
        return result;
    }

    // MAX
    template<typename T>
    template<typename Extractor>
    const T* DataFrame<T>::max(Extractor extract) const {
        if (m_data.empty()) return nullptr;
        const T* result = &m_data.front();
        auto maxValue = extract(*result);
        for (const auto &elem : m_data) {
            auto value = extract(elem);
            if (value > maxValue) {
                maxValue = value;
                result = &elem;
            }
        }
        return result;
    }

    // FILTER
    template<typename T>
    template<typename Predicate>
    std::vector<const T*> DataFrame<T>::filter(Predicate satisfies) const {
        std::vector<const T*> result;
        result.reserve(m_data.size());
        for (const auto &elem : m_data) {
            if (satisfies(elem)) {
                result.push_back(&elem);
            }
        }
        return result;
    }

    // MEAN
    template<typename T>
    template<typename ValueType, typename Extractor>
    ValueType DataFrame<T>::mean(Extractor extract) const {
        if (m_data.empty()) return ValueType{};
        ValueType sum{};
        for (const auto &elem : m_data) {
            sum += static_cast<ValueType>(extract(elem));
        }
        return sum / static_cast<ValueType>(m_data.size());
    }

    // APPLY
    template<typename T>
    template<typename F>
    void DataFrame<T>::apply(F f) const {
        for (const auto &elem : m_data) {
            f(elem);
        }
    }

} // namespace df

#endif // LIBDF_DATAFRAME_HPP