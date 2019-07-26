#ifndef MITAMA_MANA_UTILITY_IOTA_HPP
#define MITAMA_MANA_UTILITY_IOTA_HPP
#include <mitama/mana/data/value_list.hpp>
#include <mitama/mana/meta/list.hpp>
#include <mitama/mana/meta/index_range.hpp>
#include <cstdint>

namespace mitama::mana::_iota_detail {
    template <std::size_t... Range>
    auto make_iota(std::index_sequence<Range...>) {
        return value_list_of(value_c<Range>...);
    }

    template <std::size_t Lower, std::size_t Upper>
    auto iota = make_iota(make_index_range<Lower, Upper-1>{});
}

namespace mitama::mana {
    template <std::size_t Lower, std::size_t Upper>
    inline constexpr auto iota = _iota_detail::iota<Lower, Upper>;
}

#endif
