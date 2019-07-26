#ifndef MITAMA_MANA_FUNCTIONAL_METAFUNC_HPP
#define MITAMA_MANA_FUNCTIONAL_METAFUNC_HPP
#include <mitama/mana/data/type_variable.hpp>
#include <mitama/mana/data/constant_variable.hpp>

namespace mitama::mana::_detail {
    template <template <class> class Func>
    struct metafunc_wrapper_t {
        template <class T>
        using apply = typename Func<T>::type;
    };

    template <template <auto> class Func>
    struct metafunc_wrapper_v {
        template <auto V>
        static constexpr auto apply = Func<V>::value;
    };
}

namespace mitama::mana {
    template < class Func >
    struct metafunc_impl {
        template <class T>
        constexpr auto operator()(type<T>) const -> type<typename Func::template apply<T>> { return {}; }

        template <auto V>
        constexpr auto operator()(value<V>) const -> value<Func::template apply<V>> { return {}; }
    };

    template <template <class> class Func>
    inline constexpr metafunc_impl<_detail::metafunc_wrapper_t<Func>> metafunc_t{};

    template <template <auto> class Func>
    inline constexpr metafunc_impl<_detail::metafunc_wrapper_v<Func>> metafunc_v{};
}

#endif
