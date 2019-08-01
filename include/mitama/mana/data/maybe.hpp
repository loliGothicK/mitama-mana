#ifndef MITAMA_MANA_DATA_MAYBE_HPP
#define MITAMA_MANA_DATA_MAYBE_HPP
#include <mitama/mana/core/value_inject.hpp>
#include <mitama/mana/core/type_inject.hpp>
#include <mitama/mana/data/tag/data_tag.hpp>

namespace mitama::mana {
    template <auto V>
    struct just_impl_v: core::value_inject<V>, private data_type {};

    template <class T>
    struct just_impl_t: core::type_inject<T>, private data_type {};

    struct nothing_impl: private data_type {};

    template <auto V>
    inline constexpr just_impl_v<V> just_v{};

    template <class T>
    inline constexpr just_impl_t<T> just_t{};

    inline constexpr nothing_impl nothing{};
}

#endif
