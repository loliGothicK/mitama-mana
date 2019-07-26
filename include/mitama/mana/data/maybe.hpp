#ifndef MITAMA_MANA_DATA_MAYBE_HPP
#define MITAMA_MANA_DATA_MAYBE_HPP
#include <mitama/mana/core/value_inject.hpp>
#include <mitama/mana/core/type_inject.hpp>

namespace mitama::mana {
    template <auto V>
    struct just_impl_v: core::value_inject<V> {};

    template <class T>
    struct just_impl_t: core::type_inject<T> {};

    struct nothing_impl {};

    template <auto V>
    inline constexpr just_impl_v<V> just_v{};

    template <class T>
    inline constexpr just_impl_t<T> just_t{};

    inline constexpr nothing_impl nothing{};
}

#endif
