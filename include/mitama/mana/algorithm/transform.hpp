#ifndef MITAMA_MANA_ALGORITHM_TRANSFORM_HPP
#define MITAMA_MANA_ALGORITHM_TRANSFORM_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/core/metafunc.hpp>

namespace mitama::mana {
    struct transform_fn {
        template <class F, class... Types>
        constexpr auto operator()(type_list<Types...>, core::metafunc_impl<F> map) const {
            return type_list_of(map(type_c<Types>)...);
        }
        template <class F, auto... Values>
        constexpr auto operator()(value_list<Values...>, core::metafunc_impl<F> map) const {
            return value_list_of(map(value_c<Values>)...);
        }
        template <class F, auto... Values>
        constexpr auto operator()(value_list<Values...>, F map) const {
            return value_list_of(value_c<map(Values)>...);
        }
    };

    inline constexpr transform_fn transform{};
}

#endif
