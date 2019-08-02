#ifndef MITAMA_MANA_CORE_VIEW_HPP
#define MITAMA_MANA_CORE_VIEW_HPP

#include <tuple>
#include <utility>

namespace mitama::mana {

    template <class F, class G>
    struct ligature_fn {

    };

    template <class MapFn, class Xs>
    struct _view {
        Xs xs_;
        static constexpr std::size_t value = MapFn::template value<std::tuple_size_v<std::decay_t<Xs>>>;
        template <std::size_t I>
        using type = typename MapFn::template type<I, Xs>;
  
        template <class... X>
        explicit constexpr _view(X... xs): xs_(std::forward<X>(xs)...) {}

	template <std::size_t I>
	constexpr auto get()
	{ return MapFn::template get<I>(xs_); }
   };

   template <std::size_t I, class _, class Xs>
   constexpr decltype(auto) get(_view<_, Xs> const& view_) { return view_.template get<I>(); }
   template <std::size_t I, class _, class Xs>
   constexpr decltype(auto) get(_view<_, Xs>& view_) { return view_.template get<I>(); }
   template <std::size_t I, class _, class Xs>
   constexpr auto get(_view<_, Xs>&& view_) { return std::move(view_.template get<I>()); }
 
}

namespace std {
    template <std::size_t I, class MapFn, class Xs>
    struct tuple_element<I, mitama::mana::_view<MapFn, Xs>> {
        using type = typename mitama::mana::_view<MapFn, Xs>::template type<I>;
    };
    template <class MapFn, class Xs>
    struct tuple_size<mitama::mana::_view<MapFn, Xs>> {
        static constexpr auto value = mitama::mana::_view<MapFn, Xs>::value;
    };
}
#endif
