#include <catch2/catch.hpp>
#include <mitama/mana/functional/overload.hpp>

namespace mana = mitama::mana;

TEST_CASE("overload", "[functional][overload]") {
    auto f = mana::overload(
        [](void*){ return 0; },
        [](int){ return 1; },
        [](long){ return 2; },
        [](decltype(nullptr)){ return 3; }
    );

    REQUIRE(f(int{}) == 1);
    REQUIRE(f(long{}) == 2);
    REQUIRE(f(nullptr) == 3);
}
