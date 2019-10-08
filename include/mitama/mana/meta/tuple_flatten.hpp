#ifndef MITAMA_MANA_META_TUPLE_FLATTEN_HPP
#define MITAMA_MANA_META_TUPLE_FLATTEN_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/core/type_inject.hpp>
#include <mitama/mana/type_traits/is_tuple_like.hpp>
#include <mitama/mana/utility/iota.hpp>
#include <tuple>
#include <utility>

namespace mitama::mana::meta {
    template <class, class, class>
    struct atomic_tuple_cat;

    template <class... Types, class Tuple, std::size_t... Indices>
    struct atomic_tuple_cat<std::tuple<Types...>, Tuple, const value_list<Indices...>>
        : core::type_inject<std::tuple<Types..., std::tuple_element_t<Indices, Tuple>...>> {};

    template <class...>
    struct tuple_cat_type;

    template <class... Types, class Head, class... Tail>
    struct tuple_cat_type<std::tuple<Types...>, Head, Tail...>
        : tuple_cat_type<typename atomic_tuple_cat<std::tuple<Types...>, Head, decltype(mana::iota<0, std::tuple_size_v<Head>>)>::type, Tail...> {};

    template <class... Types>
    struct tuple_cat_type<std::tuple<Types...>>: core::type_inject<std::tuple<Types...>> {};

    template <class, class>
    struct tuple_flatten_impl;

    template <class Tuple, std::size_t... Indices>
    struct tuple_flatten_impl<Tuple, std::index_sequence<Indices...>>: tuple_cat_type<std::tuple_element_t<Indices, std::decay_t<Tuple>>...> {};

    template <class Tuple>
    struct tuple_flatten: tuple_flatten_impl<Tuple, std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>> {};

    template <class Tuple>
    using tuple_flatten_t = typename tuple_flatten<Tuple>::type;
}

#endif
