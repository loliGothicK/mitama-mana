#ifndef MITAMA_MANA_FUNCTIONAL_SLIDIFY_HPP
#define MITAMA_MANA_FUNCTIONAL_SLIDIFY_HPP

#include <mitama/mana/algorithm/sliding.hpp>
#include <mitama/mana/utility/apply.hpp>
#include <mitama/mana/utility/peel.hpp>
#include <mitama/mana/type_traits/is_tuple_like.hpp>
#include <tuple>

namespace mitama::mana {

template <std::size_t N>
struct slidify_fn {
    template <class... Args>
    auto operator()(Args&&... args) const {
        return mana::apply([forwarded = std::forward_as_tuple(std::forward<Args>(args)...)](auto... slide) mutable {
            return std::tuple{mana::apply([&forwarded](auto... indices) mutable {
                return std::tuple(std::get<mana::peel(indices)>(forwarded)...);
            }, mana::peel(slide))... };
        }, mana::sliding<N>(mana::iota<0, sizeof...(Args)>));
    }

    template <class TupleLike, std::enable_if_t<mana::is_tuple_like_v<std::decay_t<TupleLike>>, bool> = false>
    auto operator()(TupleLike&& t) const {
        return mana::apply([t](auto... slide) mutable {
            return std::tuple{mana::apply([&t](auto... indices) mutable {
                return std::tuple(std::get<mana::peel(indices)>(t)...);
            }, mana::peel(slide))... };
        }, mana::sliding<N>(mana::iota<0, std::tuple_size_v<std::decay_t<TupleLike>>>));
    }
};

template <std::size_t N>
inline constexpr slidify_fn<N> slidify{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_CHUNK_HPP
