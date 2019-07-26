#ifndef MITAMA_MANA_ALGORITHM_CHUNK_HPP
#define MITAMA_MANA_ALGORITHM_CHUNK_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/algorithm/transform.hpp>
#include <mitama/mana/utility/at.hpp>
#include <mitama/mana/utility/iota.hpp>
#include <mitama/mana/meta/math/multiply.hpp>
#include <mitama/mana/functional/metafunc.hpp>
#include <utility>

namespace mitama::mana::_chunk_detail {   
    template <std::size_t I, std::size_t... Indices, class... Types>
    auto make_inner_chunk(type_list<Types...> list, value_list<Indices...>) {
        return type_list_of(at<I + Indices>(list)...);
    }

    template <std::size_t... Inner, std::size_t... Outer, class... Types>
    auto make_chunk(type_list<Types...> list, value_list<Inner...> indices, value_list<Outer...>) {
        return type_list_of(type_c<decltype(make_inner_chunk<Outer>(list, indices))>...);
    }
}
namespace mitama::mana {
    template <std::size_t N>
    struct chunk_fn {
        template <class... Types>
        constexpr auto operator()(type_list<Types...> list) const {
            static_assert(sizeof...(Types) >= N);
            return _chunk_detail::make_chunk(list, iota<0, N>,
                transform(iota<0, sizeof...(Types)/N>, [](int i){ return i*N; }));
        }
    };

    template <std::size_t N>
    inline constexpr chunk_fn<N> chunk{};
}

#endif
