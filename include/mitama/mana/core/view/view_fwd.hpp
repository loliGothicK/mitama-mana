#ifndef MITAMA_MANA_CORE_VIEW_FWD_HPP
#define MITAMA_MANA_CORE_VIEW_FWD_HPP
#include <cstddef>

namespace mitama::mana {
    enum class fn { static_, dyn_ };

    template <fn, class, class>
    class _view;

    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs> const& view_);
    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs>& view_);
    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs>&& view_);
}
#endif
