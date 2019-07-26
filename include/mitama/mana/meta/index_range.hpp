#ifndef MITAMA_MANA_META_INDEX_RANGE_HPP
#define MITAMA_MANA_META_INDEX_RANGE_HPP
#include <mitama/mana/meta/concat.hpp>
#include <utility>

namespace mitama::mana::_index_range_detail {
template <class IntegerType, IntegerType First, IntegerType Last>
struct make_integer_range_impl {
  using type =
      concat_t<
        typename make_integer_range_impl<
            IntegerType, First, First + (Last - First) / 2>::type,
        typename make_integer_range_impl<
            IntegerType, First + (Last - First) / 2 + 1, Last>::type>;
};

template <class IntegerType, IntegerType Val>
struct make_integer_range_impl<IntegerType, Val, Val> {
  using type = std::integer_sequence<IntegerType, Val>;
};
} // namespace mitama::mana::_index_range_detail

namespace mitama::mana {

template <class IntegerType, std::size_t First, std::size_t Last>
using make_integer_range =
    typename _index_range_detail::make_integer_range_impl<IntegerType, First, Last>::type;

template <std::size_t First, std::size_t Last>
using make_index_range =
    typename _index_range_detail::make_integer_range_impl<std::size_t, First, Last>::type;

template <class IntegerType, IntegerType Bound>
using make_integer_sequence = make_integer_range<IntegerType, 0, Bound - 1>;

template <std::size_t Bound>
using make_index_sequence = make_index_range<0, Bound - 1>;

template <class IntegerType, class... Ts>
using integer_sequence_for = make_integer_sequence<IntegerType, sizeof...(Ts)>;

template <class... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

}
#endif
