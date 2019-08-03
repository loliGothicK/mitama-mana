#ifndef MITAMA_MANA_ALGORITHM_CHUNK_HPP
#define MITAMA_MANA_ALGORITHM_CHUNK_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/core/metafunc.hpp>

namespace mitama::mana {
    struct fold_fn {
        template <class F, class... Types>
        constexpr auto operator()(type_list<Types...>, core::metafunc_impl<F> map) const {
            return map(type_c<Types>...);
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

    inline constexpr klisli_fn klisli{};
}

#endif
