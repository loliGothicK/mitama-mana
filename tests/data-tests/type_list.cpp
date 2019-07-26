#include <catch2/catch.hpp>
#include <mitama/mana/data/type_list.hpp>
#include <type_traits>

namespace mana = mitama::mana;

TEST_CASE("type_list", "[data][type_list]") {
    REQUIRE(std::is_same_v<decltype(mana::type_list_c<int, int>), mana::type_list<int, int> const>);
}
