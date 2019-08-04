#ifndef MITAMA_MANA_FUNCTIONAL_METAFUNC_HPP
#define MITAMA_MANA_FUNCTIONAL_METAFUNC_HPP
#include <mitama/mana/data/type_variable.hpp>
#include <mitama/mana/data/constant_variable.hpp>
#include <mitama/mana/type_traits/has_type.hpp>
#include <mitama/mana/type_traits/has_value.hpp>
#include <mitama/mana/functional/overload_linearly.hpp>

namespace mitama::mana::_detail {
    template <class, class=void>
    struct apply_result_t {}; 

    template <class T>
    struct apply_result_t<T, std::enable_if_t<mana::has_type_v<T>>>
        : core::type_inject<typename T::type> {}; 

    template <class, class=void>
    struct apply_result_v {}; 

    template <class T>
    struct apply_result_v<T, std::enable_if_t<mana::has_value_v<T>>>
        : core::value_inject<T::value> {}; 

    template <template <class...> class Func>
    struct metafunc_wrapper_t {
        template <class... T>
        using apply = Func<T...>;
    };

    template <template <auto...> class Func>
    struct metafunc_wrapper_v {
        template <auto... V>
        using apply = Func<V...>;
    };
}

namespace mitama::mana::core {
    template <class> struct metafunc_impl;

    template < template <class...> class Func >
    struct metafunc_impl<_detail::metafunc_wrapper_t<Func>> {
        using Map = _detail::metafunc_wrapper_t<Func>;

        template <class... T>
        constexpr auto operator()(type<T>...) const
            -> std::enable_if_t<mana::has_value_v<typename Map::template apply<T...>>, value<Map::template apply<T...>::value>>
        { return {}; }

        template <class... T>
        constexpr auto operator()(type<T>...) const
            -> std::enable_if_t<mana::has_type_v<typename Map::template apply<T...>>, type<typename Map::template apply<T...>::type>>
        { return {}; }
    };

    template < template <auto...> class Func >
    struct metafunc_impl<_detail::metafunc_wrapper_v<Func>> {
        using Map = _detail::metafunc_wrapper_v<Func>;

        template <auto... V>
        constexpr auto operator()(value<V>...) const
            -> std::enable_if_t<mana::has_value_v<typename Map::template apply<V...>>, value<Map::template apply<V...>::value>>
        { return {}; }

        template <auto... V>
        constexpr auto operator()(value<V>...) const
            -> std::enable_if_t<mana::has_type_v<typename Map::template apply<V...>>, type<typename Map::template apply<V...>::type>>
        { return {}; }
    };

    template <template <class> class Func>
    inline constexpr metafunc_impl<_detail::metafunc_wrapper_t<Func>> metafunc_t{};

    template <template <auto> class Func>
    inline constexpr metafunc_impl<_detail::metafunc_wrapper_v<Func>> metafunc_v{};
}

#endif
