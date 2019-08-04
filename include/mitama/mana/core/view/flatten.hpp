#ifndef MITAMA_MANA_CORE_VIEW_FLATTEN_HPP
#define MITAMA_MANA_CORE_VIEW_FLATTEN_HPP
#include <mitama/mana/utility/peel.hpp>
#include <mitama/mana/algorithm/fold.hpp>
#include <mitama/mana/core/metafunc.hpp>
#include <mitama/mana/core/view/view_fwd.hpp>
#include <mitama/mana/meta/tuple_flatten.hpp>
#include <mitama/mana/functional/fix.hpp>
#include <mitama/mana/functional/overload.hpp>
#include <type_traits>
#include <tuple>

namespace mitama::mana::map_fn {

struct flatten_fn {
    template <class Tuple>
    static constexpr std::size_t value
        = mana::apply([](auto... indices) {
            return mana::peel(fold(
                list_of(value_c<std::tuple_size_v<std::decay_t<std::tuple_element_t<mana::peel(indices), Tuple>>>>...),
                [](auto... v){ return (v + ...); }
            )); }, mana::iota<0, std::tuple_size_v<Tuple>>);

    template <std::size_t I, class Tuple>
    using type = std::tuple_element_t<I, meta::tuple_flatten_t<Tuple>>;

    template <std::size_t I, class Tuple>
    static constexpr auto get(Tuple&& t) -> std::tuple_element_t<I, meta::tuple_flatten_t<Tuple>>
    {
        return mana::fix{[](auto _get, auto _value, auto _index, auto&& tup) mutable -> std::tuple_element_t<I, meta::tuple_flatten_t<Tuple>> {
            if constexpr (mana::peel(_value) < std::tuple_size_v<std::tuple_element_t<mana::peel(_index), std::decay_t<decltype(tup)>>>) {
                return mana::overload(
                    [_value, _index](auto&& tup) -> decltype(std::get<mana::peel(_index)>(std::forward<decltype(tup)>(tup)), std::declval<std::tuple_element_t<I, meta::tuple_flatten_t<Tuple>>>()) {
                        return mana::overload(
                            [_value](auto&& tup) -> decltype(std::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup))) {
                                return std::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup));
                            },
                            [_value](auto&& tup) -> decltype(mana::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup))) {
                                return mana::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup));
                            })(std::get<mana::peel(_index)>(std::forward<decltype(tup)>(tup)));
                    },
                    [_value, _index](auto&& tup) -> decltype(mana::get<mana::peel(_index)>(std::forward<decltype(tup)>(tup)), std::declval<std::tuple_element_t<I, meta::tuple_flatten_t<Tuple>>>()) {
                        return mana::overload(
                            [_value](auto&& tup) -> decltype(std::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup))) {
                                return std::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup));
                            },
                            [_value](auto&& tup) -> decltype(mana::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup))) {
                                return mana::get<mana::peel(_value)>(std::forward<decltype(tup)>(tup));
                            })(mana::get<mana::peel(_index)>(std::forward<decltype(tup)>(tup)));
                    })(std::forward<decltype(tup)>(tup));
            }
            else {
                return _get(value_c<mana::peel(_value) - std::tuple_size_v<std::tuple_element_t<mana::peel(_index), std::decay_t<decltype(tup)>>>>, value_c<mana::peel(_index) + 1>, std::forward<decltype(tup)>(tup));
            }
        }}(value_c<I>, value_c<0>, std::forward<Tuple>(t));
    }
};
}

#endif
