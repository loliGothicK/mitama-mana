#include <catch2/catch.hpp>
#include <mitama/mana/functional/chunkify.hpp>
#include <boost/type_index.hpp>
#include <iostream>

namespace mana = mitama::mana;

TEST_CASE("chunkify variadic", "[functional][chunkify]") {
    auto chunk = mana::chunkify<3>(1,2,3,4,5,6,7,8,9);

    REQUIRE(std::get<0>(chunk) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(chunk) == std::tuple{4,5,6});
    REQUIRE(std::get<2>(chunk) == std::tuple{7,8,9});
}

TEST_CASE("chunkify tuple", "[functional][chunkify]") {
    auto chunk = mana::chunkify<3>(std::tuple{1,2,3,4,5,6,7,8,9});

    REQUIRE(std::get<0>(chunk) == std::tuple{1,2,3});
    REQUIRE(std::get<1>(chunk) == std::tuple{4,5,6});
    REQUIRE(std::get<2>(chunk) == std::tuple{7,8,9});
}

TEST_CASE("chunkify view", "[functional][chunkify]") {
    auto chunk = mana::chunkify<3>.view(1,2,3,4,5,6,7,8,9);

    REQUIRE(mana::get<0>(chunk) == std::tuple{1,2,3});
    REQUIRE(mana::get<1>(chunk) == std::tuple{4,5,6});
    REQUIRE(mana::get<2>(chunk) == std::tuple{7,8,9});
}

TEST_CASE("chunkify view-map", "[functional][chunkify]") {
    auto sum = [](std::tuple<int, int, int> t){ return std::apply([](auto... v){ return (v + ...); }, t); };
    auto chunk_sum = mana::chunkify<3>.view(1,2,3,4,5,6,7,8,9).map(sum);

    REQUIRE(mana::get<0>(chunk_sum) == 6);
    REQUIRE(mana::get<1>(chunk_sum) == 15);
    REQUIRE(mana::get<2>(chunk_sum) == 24);
}

TEST_CASE("chunkify view-apply_map", "[functional][chunkify]") {
    auto sum = [](auto... v){ return (v + ...); };
    auto chunk_sum = mana::chunkify<3>.view(1,2,3,4,5,6,7,8,9).apply_map(sum);

    REQUIRE(mana::get<0>(chunk_sum) == 6);
    REQUIRE(mana::get<1>(chunk_sum) == 15);
    REQUIRE(mana::get<2>(chunk_sum) == 24);
}
