#include <catch2/catch.hpp>
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/algorithm/chunk.hpp>
#include <mitama/mana/core/metafunc.hpp>
#include <mitama/mana/utility/iota.hpp>
#include <type_traits>
#include <iostream>
#include <boost/type_index.hpp>
namespace mana = mitama::mana;

TEST_CASE("chunk<2>", "[algorithm][chunk]") {
    REQUIRE(std::is_same_v<
        decltype(mana::chunk<2>(mana::type_list_c<int, int, double, double>)),
        mana::type_list<mana::type_list<int, int>, mana::type_list<double, double>>>);

    REQUIRE(std::is_same_v<
        decltype(mana::chunk<2>(mana::iota<0, 10>)),
        mana::type_list<mana::value_list<0ul, 1ul>,
                        mana::value_list<2ul, 3ul>,
                        mana::value_list<4ul, 5ul>,
                        mana::value_list<6ul, 7ul>,
                        mana::value_list<8ul, 9ul>
                        >>);
}
