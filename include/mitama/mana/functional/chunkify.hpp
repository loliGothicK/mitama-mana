#ifndef MITAMA_MANA_FUNCTIONAL_CHUNKIFY_HPP
#define MITAMA_MANA_FUNCTIONAL_CHUNKIFY_HPP

#include <mitama/mana/algorithm/chunk.hpp>
#include <mitama/mana/algorithm/klisli.hpp>
#include <mitama/mana/utility/apply.hpp>
#include <mitama/mana/utility/peel.hpp>
#include <mitama/mana/type_traits/is_tuple_like.hpp>
#include <mitama/mana/meta/repack.hpp>
#include <mitama/mana/core/view/view.hpp>
#include <tuple>

namespace mitama::mana::map_fn {
template <std::size_t N>
struct chunkify_map_fn {
private:
    template <class Tuple, std::size_t... Indices>
    static constexpr auto element_type(Tuple&&, value_list<Indices...>) -> std::tuple<std::tuple_element_t<Indices, Tuple>...>;
public:
    template <std::size_t M>
    static constexpr std::size_t value = M / N;

    template <std::size_t I, class Tuple>
    using type = decltype(element_type(std::declval<Tuple>(), mana::iota<I*N, I*N + N>));

    template <std::size_t I, class Tuple>
    static constexpr auto get(Tuple&& t) {
        return mana::apply([&t](auto... indices){
            return std::tuple(std::get<mana::peel(indices)>(t)...);
        }, mana::peel(at<I>(mana::chunk<N>(mana::iota<0, std::tuple_size_v<std::decay_t<Tuple>>>))));
    }
};
}

namespace mitama::mana {

template <std::size_t N>
struct chunkify_fn {
    template <class... Args>
    auto operator()(Args&&... args) const {
        return mana::apply([forwarded = std::forward_as_tuple(std::forward<Args>(args)...)](auto... chunk) mutable {
            return std::tuple{mana::apply([&forwarded](auto... indices) mutable {
                return std::tuple(std::get<mana::peel(indices)>(forwarded)...);
            }, mana::peel(chunk))... };
        }, mana::chunk<N>(mana::iota<0, sizeof...(Args)>));
    }

    template <class TupleLike, std::enable_if_t<mana::is_tuple_like_v<std::decay_t<TupleLike>>, bool> = false>
    auto operator()(TupleLike&& t) const {
        return mana::apply([t](auto... chunk) mutable {
            return std::tuple{mana::apply([&t](auto... indices) mutable {
                return std::tuple(std::get<mana::peel(indices)>(t)...);
            }, mana::peel(chunk))... };
        }, mana::chunk<N>(mana::iota<0, std::tuple_size_v<std::decay_t<TupleLike>>>));
    }

    template <class... Args>
    auto view(Args&&... args) const {
        return _view<mitama::mana::map_fn::chunkify_map_fn<N>, std::tuple<Args...>>{std::forward<Args>(args)...};
    }

    template <class TupleLike, std::enable_if_t<mana::is_tuple_like_v<std::decay_t<TupleLike>>, bool> = false>
    auto view(TupleLike&& t) const {
        return std::apply([](auto&&... args){
            return _view<mitama::mana::map_fn::chunkify_map_fn<N>, std::tuple<decltype(args)...>>{std::forward<decltype(args)>(args)...};
        }, std::forward<TupleLike>(t));
    }
};

template <std::size_t N>
inline constexpr chunkify_fn<N> chunkify{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_CHUNK_HPP
