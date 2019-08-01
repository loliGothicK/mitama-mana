#ifndef MITAMA_MANA_TYPE_TRAITS_HAS_TYPE_HPP
#define MITAMA_MANA_TYPE_TRAITS_HAS_TYPE_HPP
#include <type_traits>

namespace mitama::mana {
template < class T, class = void >
struct has_type: std::false_type {};

template < class T >
struct has_type<T, std::void_t<typename std::decay_t<T>::type>>: std::true_type {};

template <class T>
inline constexpr bool has_type_v = has_type<T>::value;
}

#endif
