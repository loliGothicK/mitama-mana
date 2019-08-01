#include <catch2/catch.hpp>
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/algorithm/transform.hpp>
#include <mitama/mana/core/metafunc.hpp>
#include <type_traits>
#include <iostream>
#include <boost/type_index.hpp>
namespace mana = mitama::mana;

TEST_CASE("transform", "[algorithm][transform]") {
    REQUIRE(std::is_same_v<
        decltype(mana::transform(mana::type_list_c<int, int>, mana::core::metafunc_t<std::add_const>)),
        mana::type_list<const int, const int>>);
    constexpr auto transformed = mana::transform(mana::value_list_c<1, 2>, [](int i){ return i * 2; });
    REQUIRE(std::is_same_v<
        decltype(transformed),
        mana::value_list<2, 4> const>);
}
