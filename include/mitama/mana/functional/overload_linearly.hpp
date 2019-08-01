#ifndef MITAMA_MANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP
#define MITAMA_MANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP

#include <utility>
#include <type_traits>

namespace mitama::mana {

template <class F, class G>
struct overload_linearly_impl {
    F f;
    G g;

private:
    template <class... Args>
    constexpr std::enable_if_t<std::is_invocable_v<F, Args...>, F const&>
    which(int) const& { return f; }

    template <class... Args>
    constexpr std::enable_if_t<std::is_invocable_v<F, Args...>, F&>
    which(int) & { return f; }

    template <class... Args>
    constexpr std::enable_if_t<std::is_invocable_v<F, Args...>, F&&>
    which(int) && { return std::move(f); }

    template <class...>
    constexpr G const& which(...) const& { return g; }

    template <class...>
    constexpr G& which(...) & { return g; }

    template <class...>
    constexpr G&& which(...) && { return std::move(g); }

public:
    template <class... Args>
    constexpr decltype(auto) operator()(Args&& ...args) const&
    { return which<Args&&...>(0)(std::forward<Args>(args)...); }

    template <class... Args>
    constexpr decltype(auto) operator()(Args&& ...args) &
    { return which<Args&&...>(0)(std::forward<Args>(args)...); }

    template <class... Args>
    constexpr decltype(auto) operator()(Args&& ...args) &&
    { return which<Args&&...>(0)(std::forward<Args>(args)...); }
};

struct overload_linearly_delegate {
    template <class F, class G>
    constexpr overload_linearly_impl<std::decay_t<F>, std::decay_t<G>>
    operator()(F&& f, G&& g) const {
        return {std::forward<F>(f), std::forward<G>(g)};
    }

    template <class F, class G, class ...H>
    constexpr decltype(auto) operator()(F&& f, G&& g, H&& ...h) const {
        return (*this)(std::forward<F>(f), (*this)(std::forward<G>(g), std::forward<H>(h)...));
    }

    template <class F>
    constexpr std::decay<F> operator()(F&& f) const {
        return std::forward<F>(f);
    }
};

constexpr overload_linearly_delegate overload_linearly{};

}

#endif // !MITAMA_MANA_FUNCTIONAL_OVERLOAD_LINEARLY_HPP
