#ifndef MITAMA_MANA_DATA_TYPE_LIST_HPP
#define MITAMA_MANA_DATA_TYPE_LIST_HPP
#include <mitama/mana/data/type_variable.hpp>
#include <mitama/mana/data/tag/data_tag.hpp>

namespace mitama::mana {
    template <class...>
    struct type_list: private data_type {};

    template <class... Xs>
    inline constexpr type_list<Xs...> type_list_c{};

    template <class... Xs>
    inline constexpr auto type_list_of(type<Xs>...) { return type_list_c<Xs...>; };

    template <class... Xs>
    inline constexpr auto list_of(type<Xs>...) { return type_list_c<Xs...>; };
}

#endif
