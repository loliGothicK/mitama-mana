#ifndef MITAMA_MANA_FUNCTIONAL_OVERLOAD_HPP
#define MITAMA_MANA_FUNCTIONAL_OVERLOAD_HPP

#include <type_traits>
#include <utility>

namespace mitama::mana {

template <class F, class ...G>
struct overload_t
    : overload_t<F>::type
    , overload_t<G...>::type
{
    using type = overload_t;
    using overload_t<F>::type::operator();
    using overload_t<G...>::type::operator();

    template <class F_, class ...G_>
    constexpr explicit overload_t(F_&& f, G_&& ...g)
        : overload_t<F>::type(static_cast<F_&&>(f))
        , overload_t<G...>::type(static_cast<G_&&>(g)...)
    { }
};

template <class F>
struct overload_t<F> { using type = F; };

template <class R, class ...Args>
struct overload_t<R(*)(Args...)> {
    using type = overload_t;
    R (*fptr_)(Args...);

    explicit constexpr overload_t(R (*fp)(Args...))
        : fptr_(fp)
    { }

    constexpr R operator()(Args ...args) const
    { return fptr_(static_cast<Args&&>(args)...); }
};

struct make_overload_t {
    template <class ...F>
    constexpr auto operator()(F&& ...f) const {
        return overload_t<std::decay_t<F>...>(std::forward<F>(f)...);
    }
};

constexpr make_overload_t overload{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_OVERLOAD_HPP
