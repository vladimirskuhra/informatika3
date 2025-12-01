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
    /*inline*/ void DataFrame<T>::print(std::ostream &ost) const /*inline na zaciatok v tomto pripade netreba pisat */
    {
        //void(ost); //aby sme sa zbavili varovania/warningu o nepouzitej premennej
    }

    template <typename T>
    inline size_t DataFrame<T>::size() const
    {
        return m_data.size(); //vratime velkost vektora m_data - pocet prvkov dataframu/vektora - dost dobre
    }

} // namespace df

#endif
