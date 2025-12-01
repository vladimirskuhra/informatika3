#ifndef LIBDF_DATAFRAME_HPP
#define LIBDF_DATAFRAME_HPP

#include <vector>
#include <iostream>

namespace df {

    template<typename T>
    class DataFrame
    {

        public:
            DataFrame(std::vector<T> data);
            void print(std::ostream &ost) const;
            size_t size() const;
            void print() const;

        private:
            std::vector<T> m_data;  
        
    };
    /*pozname presuvaci konstruktor, je to jednoduchsie ako kopirovanie*/
    template <typename T>
    inline DataFrame<T>::DataFrame(std::vector<T> data) 
    :m_data(std::move(data)) // presuvaci konstruktor, nebudeme data kopirovat ale budeme ich presuvat
    {

    }

    template <typename T>
    void DataFrame<T>::print(std::ostream &ost) const
    {
        for (const auto &item : m_data)
            ost << item << "\n";
    }

    template <typename T>
    void df::DataFrame<T>::print() const {
        print(std::cout);
    }

    template <typename T>
    inline size_t DataFrame<T>::size() const
    {
        return m_data.size(); //vratime velkost vektora m_data - pocet prvkov dataframu/vektora - dost dobre
    }

} // namespace df

#endif
