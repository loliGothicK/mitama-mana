#include <catch2/catch.hpp>
#include <mitama/mana/functional/overload_linearly.hpp>

namespace mana = mitama::mana;

TEST_CASE("overload_linearly", "[functional][overload_linearly]") {
    auto f = mana::overload_linearly(
        [](void*){ return 0; },
        [](int){ return 1; },
        [](long){ return 2; },
        [](decltype(nullptr)){ return 3; }
    );

    REQUIRE(f(int{}) == 1);
    REQUIRE(f(long{}) == 1);
    REQUIRE(f(nullptr) == 0);
}
