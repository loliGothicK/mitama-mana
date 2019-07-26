#ifndef MITAMA_MANA_META_MATH_MULTIPLY_HPP
#define MITAMA_MANA_META_MATH_MULTIPLY_HPP
#include <mitama/mana/core/value_inject.hpp>
namespace mitama::mana {
    template <auto A, auto B>
    struct multiply: core::value_inject<A*B> {};
}

#endif
