#ifndef MITAMA_MANA_TYPE_TRAITS_IS_TUPLE_LIKE_HPP
#define MITAMA_MANA_TYPE_TRAITS_IS_TUPLE_LIKE_HPP
#include <mitama/mana/type_traits/has_type.hpp>
#include <mitama/mana/type_traits/has_value.hpp>
#include <cstddef>
#include <utility>
#include <type_traits>
#include <tuple>

namespace mitama::mana::_is_tuple_like_detail {
template < class, class, class = void > struct is_tuple_like_detail: std::false_type {};

template < class T, std::size_t... I >
struct is_tuple_like_detail<T, std::index_sequence<I...>, std::void_t<decltype(std::get<I>(std::declval<T>()))...>>
  : std::conjunction<has_type<std::tuple_element<I, T>>...>
{};

template < class TupleLike >
struct is_tuple_like_impl: is_tuple_like_detail<TupleLike, std::make_index_sequence<std::tuple_size_v<TupleLike>>> {};
}

namespace mitama::mana {
/// is_tuple_like
/// requires
///   std::tuple_element<0, T>
///   std::tuple_size_v<T>
///   (T t) { std::get<0>(t) }
template < class T >
struct is_tuple_like
  : std::conjunction<
      has_value<std::tuple_size<T>>,
      _is_tuple_like_detail::is_tuple_like_impl<T>
    >
{};

template <class T>
inline constexpr bool is_tuple_like_v = is_tuple_like<T>::value;
}

#endif
