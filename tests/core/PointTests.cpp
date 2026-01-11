#include <tests/catch.hpp>

#include <seraph/core/Point.hpp>

TEST_CASE("point construction", "[Point]") {
    
    SECTION("default points are constructed with coordinates (0, 0)") {
        const auto point = Point();
        REQUIRE(point.x() == 0.0f);
        REQUIRE(point.y() == 0.0f);
    }

    SECTION("points can be constructed memberwise") {
        const auto point = Point(1.2f, 3.4f);
        REQUIRE(point.x() == 1.2f);
        REQUIRE(point.y() == 3.4f);
    }

    SECTION("points can be copied") {
        const auto point = Point(1.2f, 3.4f);
        const auto other = Point(point);
        REQUIRE(other.x() == point.x());
        REQUIRE(other.y() == point.y());
    }
}
