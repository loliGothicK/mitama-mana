#ifndef MITAMA_MANA_DATA_CONSTANT_VARIABLE_HPP
#define MITAMA_MANA_DATA_CONSTANT_VARIABLE_HPP
#include <mitama/mana/core/value_inject.hpp>
#include <mitama/mana/data/tag/data_tag.hpp>

namespace mitama::mana {
    template <auto V>
    struct value: core::value_inject<V>, private data_type {};

    template <auto V>
    inline constexpr value<V> value_c{};
}

#endif
