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

TEST_CASE("chunkify map", "[functional][chunkify]") {
    auto chunk = mana::chunkify<3>.view(1,2,3,4,5,6,7,8,9);
    std::cout << boost::typeindex::type_id_with_cvr<decltype(mana::get<0>(chunk))>().pretty_name() << std::endl;
    REQUIRE(mana::get<0>(chunk) == std::tuple{1,2,3});
    REQUIRE(mana::get<1>(chunk) == std::tuple{4,5,6});
    REQUIRE(mana::get<2>(chunk) == std::tuple{7,8,9});
}
