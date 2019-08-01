#ifndef MITAMA_MANA_FUNCTIONAL_FIX_HPP
#define MITAMA_MANA_FUNCTIONAL_FIX_HPP

#include <utility>

namespace mitama::mana {
template <class F>
struct fix {
    F f;

    template <class... X>
    constexpr decltype(auto) operator()(X&& ...x) &
    { return f(fix<F&>{f}, std::forward<X>(x)...); }

    template <class... X>
    constexpr decltype(auto) operator()(X&& ...x) const&
    { return f(fix<F const&>{f}, std::forward<X>(x)...); }

    template <class... X>
    constexpr decltype(auto) operator()(X&& ...x) &&
    { return std::move(f)(fix<F&>{f}, std::forward<X>(x)...); }
};

template <class F>
fix(F&&) -> fix<F>;
}

#endif // !MITAMA_MANA_FUNCTIONAL_FIX_HPP
