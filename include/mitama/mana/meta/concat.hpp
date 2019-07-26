#ifndef MITAMA_MANA_META_CONCAT_HPP
#define MITAMA_MANA_META_CONCAT_HPP
#include <mitama/mana/core/type_inject.hpp>
#include <utility>

namespace mitama::mana {
template<class, class>
struct concat;

template <template <class...> class TT, class... L, class... R>
struct concat<TT<L...>, TT<R...>>: core::type_inject<TT<L..., R...>> {};

template <template <class Ty, Ty...> class TT, class T, T... L, T... R>
struct concat<TT<T, L...>, TT<T, R...>>: core::type_inject<TT<T, L..., R...>> {};

template <class L, class R>
using concat_t = typename concat<L, R>::type;

}
#endif
