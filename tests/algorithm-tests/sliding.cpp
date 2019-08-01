#include <catch2/catch.hpp>
#include <mitama/mana/data/type_list.hpp>
#include <mitama/mana/algorithm/sliding.hpp>
#include <type_traits>
#include <iostream>
#include <boost/type_index.hpp>
namespace mana = mitama::mana;

TEST_CASE("sliding<2>", "[algorithm][chunk]") {
    REQUIRE(std::is_same_v<
        decltype(mana::sliding<2>(mana::type_list_c<int, int, double, double>)),
        mana::type_list<mana::type_list<int, int>,
                        mana::type_list<int, double>,
                        mana::type_list<double, double>
                        >>);
}
