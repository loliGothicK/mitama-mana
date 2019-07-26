#ifndef MITAMA_MANA_META_LIST_HPP
#define MITAMA_MANA_META_LIST_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <cstdint>

namespace mitama::mana::meta {
    template <std::size_t, class>
    struct list_element;

    template <std::size_t I, template <class...> class TList, class Head, class... Tail>
    struct list_element<I, TList<Head, Tail...>>: list_element<I-1, TList<Tail...>> {};

    template <template <class...> class TList, class Head, class... Tail>
    struct list_element<0, TList<Head, Tail...>>: core::type_inject<Head> {};

    template <std::size_t I, template <auto...> class VList, auto Head, auto... Tail>
    struct list_element<I, VList<Head, Tail...>>: list_element<I-1, VList<Tail...>> {};

    template <template <auto...> class VList, auto Head, auto... Tail>
    struct list_element<0, VList<Head, Tail...>>: core::value_inject<Head> {};

    template <std::size_t I, class List >
    using list_element_t = typename list_element<I, List>::type;

    template <std::size_t I, class List >
    inline constexpr auto list_element_v = list_element<I, List>::value;
}

#endif
