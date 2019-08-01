#ifndef MITAMA_MANA_UTILITY_AT_HPP
#define MITAMA_MANA_UTILITY_AT_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/meta/list.hpp>
#include <cstdint>

namespace mitama::mana {
    template <std::size_t I>
    struct at_fn {
        template <class... Types>
        constexpr auto operator()(type_list<Types...>) const
            { return type_c<meta::list_element_t<I, type_list<Types...>>>; }

        template <auto... Values>
        constexpr auto operator()(value_list<Values...>) const
            { return value_c<meta::list_element_v<I, value_list<Values...>>>; }
    };

    template <std::size_t I>
    inline constexpr at_fn<I> at{};
}

#endif
