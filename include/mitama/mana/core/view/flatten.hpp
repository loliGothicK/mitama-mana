#ifndef MITAMA_MANA_CORE_VIEW_FLATTEN_HPP
#define MITAMA_MANA_CORE_VIEW_FLATTEN_HPP
#include <type_traits>
#include <tuple>
#include <mitama/mana/core/view/view_fwd.hpp>

namespace mitama::mana::map_fn {
template <class F>
struct flatten_fn {
    template <std::size_t N>
    static constexpr std::size_t value = N;

    template <std::size_t I, class Tuple>
    using type = std::invoke_result_t<F, std::tuple_element_t<I, Tuple>>;

    template <std::size_t I, class Tuple>
    constexpr auto get(Tuple&& t) -> decltype(map_(std::get<I>(std::forward<Tuple>(t))))
    { return map_(std::get<I>(std::forward<Tuple>(t))); }

    template <std::size_t I, class Tuple>
    constexpr auto get(Tuple&& t) -> decltype(map_(mana::get<I>(std::forward<Tuple>(t))))
    { return map_(mana::get<I>(std::forward<Tuple>(t))); }
};
}

#endif
