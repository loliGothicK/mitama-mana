#ifndef MITAMA_MANA_FUNCTIONAL_SLIDIFY_HPP
#define MITAMA_MANA_FUNCTIONAL_SLIDIFY_HPP

#include <mitama/mana/algorithm/sliding.hpp>
#include <mitama/mana/utility/apply.hpp>
#include <mitama/mana/utility/peel.hpp>
#include <mitama/mana/type_traits/is_tuple_like.hpp>
#include <mitama/mana/core/view/view.hpp>
#include <tuple>

namespace mitama::mana::map_fn {
template <std::size_t N>
struct slidify_map_fn {
    template <class Tuple, std::size_t... Indices>
    static constexpr auto element_type(Tuple&&, value_list<Indices...>) -> std::tuple<std::tuple_element_t<Indices, Tuple>...>;
    template <class Tuple>
    static constexpr std::size_t value = std::tuple_size_v<std::decay_t<Tuple>> - N + 1;

    template <std::size_t I, class Tuple>
    using type = decltype(element_type(std::declval<Tuple>(), mana::iota<I, I + N>));

    template <std::size_t I, class Tuple>
    static constexpr auto get(Tuple&& t) {
        return mana::apply([&t](auto... indices){
            return std::tuple(std::get<mana::peel(indices)>(t)...);
        }, mana::iota<I, I + N>);
    }
};
}


namespace mitama::mana {

template <std::size_t Begin, std::size_t Step>
struct stridify_fn {
    template <class... Args>
    auto operator()(Args&&... args) const {
        return mana::apply([forwarded = std::forward_as_tuple(std::forward<Args>(args)...)](auto... slide) mutable {
            return std::tuple{mana::apply([&forwarded](auto... indices) mutable {
                return std::tuple(std::get<mana::peel(indices)>(forwarded)...);
            }, mana::peel(slide))... };
        }, mana::sliding<N>(mana::iota<0, sizeof...(Args)>));
    }
};

template <std::size_t Begin, std::size_t Step>
inline constexpr stridify_fn<Begin, Step> stridify{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_CHUNK_HPP
