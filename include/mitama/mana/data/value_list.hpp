#ifndef MITAMA_MANA_DATA_VALUE_LIST_HPP
#define MITAMA_MANA_DATA_VALUE_LIST_HPP
#include <mitama/mana/data/constant_variable.hpp>
#include <mitama/mana/data/tag/data_tag.hpp>
#include <mitama/mana/meta/index_range.hpp>

namespace mitama::mana::_detail {
    template <template <auto...> class, class>
    struct repack;

    template <template <auto...> class RePack, template <auto...> class Pack, auto... Values>
    struct repack<RePack, Pack<Values...>>: core::type_inject<RePack<Values...>> {};

    template <template <auto...> class RePack, template <class T, T...> class Pack, class Ty, Ty... Values>
    struct repack<RePack, Pack<Ty, Values...>>: core::type_inject<RePack<Values...>> {};

    template <template <auto...> class RePack, class Pack>
    using repacked_indices = typename repack<RePack, Pack>::type;
}


namespace mitama::mana {
    template <auto...>
    struct value_list: private data_type {};

    template <auto... Xs>
    inline constexpr value_list<Xs...> value_list_c{};

    template <auto Low, auto Up>
    inline constexpr auto value_range = _detail::repacked_indices<value_list, make_index_range<Low, Up>>{};

    template <auto... Xs>
    inline constexpr auto value_list_of(value<Xs>...) { return value_list_c<Xs...>; };

    template <auto... Xs>
    inline constexpr auto list_of(value<Xs>...) { return value_list_c<Xs...>; };
}

#endif
