#ifndef MITAMA_MANA_CORE_VIEW_HPP
#define MITAMA_MANA_CORE_VIEW_HPP

#include <tuple>
#include <utility>
#include <mitama/mana/core/view/map.hpp>
#include <mitama/mana/core/view/apply_map.hpp>
#include <mitama/mana/core/view/flatten.hpp>

namespace mitama::mana {

    template <class F, class View, std::size_t... Indices>
    inline constexpr auto apply_view_impl(F&& f, View&& view, std::index_sequence<Indices...>)
    { return std::invoke(std::forward<F>(f), mana::get<Indices>(view)...); }

    template <class F, class View>
    inline constexpr auto apply_view(F&& f, View&& view)
    { return apply_view_impl(std::forward<F>(f), std::forward<View>(view), std::make_index_sequence<std::decay_t<View>::value>{}); }

    template <class MapFn, class Xs>
    class _view<fn::static_, MapFn, Xs> {
        Xs xs_;
    public:
        static constexpr std::size_t value = MapFn::template value<Xs>;
        template <std::size_t I>
        using type = typename MapFn::template type<I, Xs>;
  
        template <class... X>
        explicit constexpr _view(X... xs): xs_(std::forward<X>(xs)...) {}

        template <std::size_t I>
        constexpr auto get()
        { return MapFn::template get<I>(xs_); }

        template <class F>
        constexpr auto map(F&& f)
        { return _view<fn::dyn_, map_fn::transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)); }

        template <class F>
        constexpr auto apply_map(F&& f)
        { return _view<fn::dyn_, map_fn::apply_transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)); }

        template <template<class T, class = std::allocator<T>> class Container>
        constexpr auto collect()
        { return apply_view([](auto&&... args){ return Container{ std::forward<decltype(args)>(args)... }; }, *this); }

        constexpr auto flatten()
        { return _view<fn::static_, map_fn::flatten_fn, _view>(std::move(*this)); }

        template <class F>
        constexpr auto flat_map(F&& f)
        { return _view<fn::dyn_, map_fn::transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)).flatten(); }
    };

    template <class MapFn, class Xs>
    class _view<fn::dyn_, MapFn, Xs> {
        Xs xs_;
        MapFn map_;
    public:
        static constexpr std::size_t value = MapFn::template value<Xs>;
        template <std::size_t I>
        using type = typename MapFn::template type<I, Xs>;
  
        template <class F, class... X>
        explicit constexpr _view(F&& f, X... xs): xs_(std::forward<X>(xs)...), map_(std::forward<F>(f)) {}

        template <class F>
        explicit constexpr _view(F&& f, Xs&& xs): xs_(std::move(xs)), map_{std::forward<F>(f)} {}

        template <std::size_t I>
        constexpr auto get()
        { return map_.template get<I>(xs_); }

        template <class F>
        constexpr auto map(F&& f)
        { return _view<fn::dyn_, map_fn::transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)); }

        template <class F>
        constexpr auto apply_map(F&& f)
        { return _view<fn::dyn_, map_fn::apply_transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)); }

        template <template<class T, class = std::allocator<T>> class Container>
        constexpr auto collect()
        { return apply_view([](auto&&... args){ return Container{ std::forward<decltype(args)>(args)... }; }, *this); }

        constexpr auto flatten()
        { return _view<fn::static_, map_fn::flatten_fn, _view>(std::move(*this)); }
        template <class F>

        constexpr auto flat_map(F&& f)
        { return _view<fn::dyn_, map_fn::transform_fn<F>, _view>(std::forward<F>(f), std::move(*this)).flatten(); }
    };

    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs> const& view_) { return view_.template get<I>(); }
    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs>& view_) { return view_.template get<I>(); }
    template <std::size_t I, fn _fn, class _, class Xs>
    inline constexpr decltype(auto) get(_view<_fn, _, Xs>&& view_) { return std::move(view_.template get<I>()); }
 
}

namespace std {
    template <mitama::mana::fn fn_, std::size_t I, class MapFn, class Xs>
    struct tuple_element<I, mitama::mana::_view<fn_, MapFn, Xs>> {
        using type = typename mitama::mana::_view<fn_, MapFn, Xs>::template type<I>;
    };
    template <mitama::mana::fn fn_, class MapFn, class Xs>
    struct tuple_size<mitama::mana::_view<fn_, MapFn, Xs>> {
        static constexpr auto value = mitama::mana::_view<fn_, MapFn, Xs>::value;
    };
}
#endif
