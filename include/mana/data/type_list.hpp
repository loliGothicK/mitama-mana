#ifndef MITAMA_MANA_DATA_TYPE_LIST_HPP
#define MITAMA_MANA_DATA_TYPE_LIST_HPP

namespace mitama::mana {
    template <class...>
    struct type_list {};

    template <class... Xs>
    inline constexpr type_list<Xs...> type_list_c{};
}

#endif
