#ifndef MITAMA_MANA_TYPE_TRAITS_HAS_VALUE_HPP
#define MITAMA_MANA_TYPE_TRAITS_HAS_VALUE_HPP
#include <type_traits>

namespace mitama::mana {
template < class T, class = void >
struct has_value: std::false_type {};

template < class T >
struct has_value<T, std::void_t<decltype(std::decay_t<T>::value)>>: std::true_type {};

template <class T>
inline constexpr bool has_value_v = has_value<T>::value;
}

#endif
