#ifndef MITAMA_MANA_META_REPACK_HPP
#define MITAMA_MANA_META_REPACK_HPP
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/core/type_inject.hpp>

namespace mitama::mana::meta {
    template <template <class...> class, class>
    struct repack;

    template <template <class...> class RePack, template <class...> class Pack, class... Types>
    struct repack<RePack, Pack<Types...>>: core::type_inject<RePack<RePack<Types...>>> {};

    template <template <class...> class RePack, class Pack>
    using repack_t = typename repack<RePack, Pack>::type;
}

#endif
