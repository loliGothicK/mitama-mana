#include <catch2/catch.hpp>
#include <mitama/mana/functional/chunkify.hpp>
#include <boost/type_index.hpp>
#include <iostream>

namespace mana = mitama::mana;

TEST_CASE("chunkify", "[functional][chunkify]") {
    auto chunk = mana::chunkify<3>(1,2,3,4,5,6,7,8,9);

    REQUIRE(std::get<0>(chunk) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(chunk) == std::tuple{4,5,6});
    REQUIRE(std::get<2>(chunk) == std::tuple{7,8,9});
}
