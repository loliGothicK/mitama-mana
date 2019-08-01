#ifndef MITAMA_MANA_UTILITY_APPLY_HPP
#define MITAMA_MANA_UTILITY_APPLY_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/meta/list.hpp>
#include <cstdint>

namespace mitama::mana {
    struct apply_fn {
        template <class F, class... Types>
        constexpr auto operator()(F&& f, type_list<Types...>) const
        { return std::forward<F>(f)(type_c<Types>...); }

        template <class F, auto... Values>
        constexpr auto operator()(F&& f, value_list<Values...>) const
        { return std::forward<F>(f)(value_c<Values>...); }
    };

    inline constexpr apply_fn apply{};
}

#endif
