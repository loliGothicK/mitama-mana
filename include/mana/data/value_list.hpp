#ifndef MITAMA_MANA_DATA_VALUE_LIST_HPP
#define MITAMA_MANA_DATA_VALUE_LIST_HPP

namespace mitama::mana {
    template <auto...>
    struct value_list {};

    template <auto... Xs>
    inline constexpr value_list<Xs...> value_list_c{};
}

#endif
