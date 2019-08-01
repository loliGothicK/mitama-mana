#include <catch2/catch.hpp>
#include <mitama/mana/functional/fix.hpp>

namespace mana = mitama::mana;

TEST_CASE("fix", "[functional][fix]") {
    auto factorial = mana::fix{[](auto fact, auto n) -> int {
        if (n == 0) return 1;
        else        return n * fact(n - 1);
    }};
    REQUIRE(factorial(4) == 24);
    REQUIRE(factorial(5) == 120);
    REQUIRE(factorial(6) == 720);
}
