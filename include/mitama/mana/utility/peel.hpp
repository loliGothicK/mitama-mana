#ifndef MITAMA_MANA_UTILITY_PEEL_HPP
#define MITAMA_MANA_UTILITY_PEEL_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/meta/list.hpp>
#include <cstdint>

namespace mitama::mana {
    struct peel_fn {
        template <class T, std::enable_if_t<is_data_type_v<T>, bool> = false>
        constexpr auto operator()(type<T>) const
        { return T{}; }

        template <auto V>
        constexpr auto operator()(value<V>) const
        { return V; }
    };

    inline constexpr peel_fn peel{};
}

#endif
