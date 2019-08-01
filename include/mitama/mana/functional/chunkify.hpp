#ifndef MITAMA_MANA_FUNCTIONAL_CHUNK_HPP
#define MITAMA_MANA_FUNCTIONAL_CHUNK_HPP

#include <mitama/mana/algorithm/chunk.hpp>
#include <mitama/mana/utility/apply.hpp>
#include <mitama/mana/utility/peel.hpp>
#include <tuple>

namespace mitama::mana {

template <std::size_t N>
struct chunkify_fn {
    template <class... Args>
    auto operator()(Args&&... args) const {
        return mana::apply([forwarded = std::forward_as_tuple(std::forward<Args>(args)...)](auto... chunk) mutable {
            return std::tuple{mana::apply([&forwarded](auto... indices) mutable {
                return std::tuple(std::get<peel(indices)>(forwarded)...);
            }, mana::peel(chunk))... };
        }, mana::chunk<N>(mana::iota<0, sizeof...(Args)>));
    }
};

template <std::size_t N>
inline constexpr chunkify_fn<N> chunkify{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_CHUNK_HPP
