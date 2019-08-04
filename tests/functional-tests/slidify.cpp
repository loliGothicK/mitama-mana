#include <catch2/catch.hpp>
#include <mitama/mana/functional/slidify.hpp>
#include <boost/type_index.hpp>
#include <iostream>

namespace mana = mitama::mana;

TEST_CASE("slidify variadic", "[functional][slidify]") {
    auto sliding = mana::slidify<3>(1,2,3,4,5,6);

    REQUIRE(std::get<0>(sliding) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(sliding) == std::tuple{2,3,4});
    REQUIRE(std::get<2>(sliding) == std::tuple{3,4,5});
    REQUIRE(std::get<3>(sliding) == std::tuple{4,5,6});
}


TEST_CASE("slidify tuple", "[functional][slidify]") {
    auto sliding = mana::slidify<3>(std::tuple{1,2,3,4,5,6});

    REQUIRE(std::get<0>(sliding) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(sliding) == std::tuple{2,3,4});
    REQUIRE(std::get<2>(sliding) == std::tuple{3,4,5});
    REQUIRE(std::get<3>(sliding) == std::tuple{4,5,6});
}

TEST_CASE("slidify view", "[functional][slidify]") {
    auto sliding_view = mana::slidify<3>.view(1,2,3,4,5,6);

    REQUIRE(mana::get<0>(sliding_view) == std::tuple{1,2,3});
    REQUIRE(mana::get<1>(sliding_view) == std::tuple{2,3,4});
    REQUIRE(mana::get<2>(sliding_view) == std::tuple{3,4,5});
    REQUIRE(mana::get<3>(sliding_view) == std::tuple{4,5,6});
}

TEST_CASE("slidify view-map", "[functional][slidify]") {
    auto sum = [](std::tuple<int, int, int> t){ return std::apply([](auto... v){ return (v + ...); }, t); };
    auto sliding_sum = mana::slidify<3>.view(1,2,3,4,5,6).map(sum);

    REQUIRE(mana::get<0>(sliding_sum) == 6);
    REQUIRE(mana::get<1>(sliding_sum) == 9);
    REQUIRE(mana::get<2>(sliding_sum) == 12);
    REQUIRE(mana::get<3>(sliding_sum) == 15);
}

TEST_CASE("slidify view-apply_map", "[functional][slidify]") {
    auto sum = [](auto... v){ return (v + ...); };
    auto sliding_sum = mana::slidify<3>.view(1,2,3,4,5,6).apply_map(sum);

    REQUIRE(mana::get<0>(sliding_sum) == 6);
    REQUIRE(mana::get<1>(sliding_sum) == 9);
    REQUIRE(mana::get<2>(sliding_sum) == 12);
    REQUIRE(mana::get<3>(sliding_sum) == 15);
}

TEST_CASE("slidify-flatten", "[functional][chunkify]") {
    mana::apply_view(
        [](auto... values) {
            REQUIRE(std::tuple{values...} == std::tuple{1,2,3,2,3,4,3,4,5,4,5,6});
        },
        mana::slidify<3>.view(1,2,3,4,5,6).flatten()
    );
}
