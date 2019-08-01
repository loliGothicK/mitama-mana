#ifndef MITAMA_MANA_DATA_TAG_DATA_TAG_HPP
#define MITAMA_MANA_DATA_TAG_DATA_TAG_HPP
#include <type_traits>

namespace mitama::mana {
    class data_type {};

    template <class T>
    struct is_data_type: std::is_base_of<data_type, T> {};

    template <class T>
    inline constexpr bool is_data_type_v = is_data_type<T>::value;
}

#endif
