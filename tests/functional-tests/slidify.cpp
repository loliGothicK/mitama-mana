#include <catch2/catch.hpp>
#include <mitama/mana/functional/slidify.hpp>
#include <boost/type_index.hpp>
#include <iostream>

namespace mana = mitama::mana;

TEST_CASE("slidify variadic", "[functional][slidify]") {
    auto slided = mana::slidify<3>(1,2,3,4,5,6);

    REQUIRE(std::get<0>(slided) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(slided) == std::tuple{2,3,4});
    REQUIRE(std::get<2>(slided) == std::tuple{3,4,5});
    REQUIRE(std::get<3>(slided) == std::tuple{4,5,6});
}


TEST_CASE("slidify tuple", "[functional][slidify]") {
    auto slided = mana::slidify<3>(std::tuple{1,2,3,4,5,6});

    REQUIRE(std::get<0>(slided) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(slided) == std::tuple{2,3,4});
    REQUIRE(std::get<2>(slided) == std::tuple{3,4,5});
    REQUIRE(std::get<3>(slided) == std::tuple{4,5,6});
}


