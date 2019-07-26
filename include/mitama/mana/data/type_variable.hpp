#ifndef MITAMA_MANA_DATA_TYPE_VARIABLE_HPP
#define MITAMA_MANA_DATA_TYPE_VARIABLE_HPP
#include <mitama/mana/core/type_inject.hpp>
namespace mitama::mana {
    template <class T>
    struct type: core::type_inject<T> {};

    template <class T>
    inline constexpr type<T> type_c{};
}

#endif
