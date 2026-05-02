#include <tests/catch.hpp>

#include <seraph/core/Point.hpp>

TEST_CASE("Point", "[Point]") {

    SECTION("Point()") {
        const auto point = Point();
        REQUIRE(point == Point(0.0f, 0.0f));
    }

    SECTION("Point(x, y)") {
        const auto point = Point(1.2f, 3.4f);
        REQUIRE(point == Point(1.2f, 3.4f));
    }

    SECTION("Point(other)") {
        const auto point = Point(1.2f, 3.4f);
        const auto other = Point(point);
        REQUIRE(point == other);
    }

    SECTION("operator<=>(other)") {
        const auto small = Point(1.2f, 3.4f);
        const auto large = Point(5.6f, 7.8f);
        REQUIRE(small < large);
        REQUIRE(large > small);
        REQUIRE(small <= small);
        REQUIRE(small <= large);
        REQUIRE(large >= small);
        REQUIRE(large >= large);
        REQUIRE(small == small);
        REQUIRE(small != large);
        REQUIRE((small <=> large) == std::strong_ordering::less);
        REQUIRE((small <=> small) == std::strong_ordering::equal);
        REQUIRE((large <=> small) == std::strong_ordering::greater);
    }

    SECTION("getters") {
        const auto point = Point(1.2f, 3.4f);
        REQUIRE(point.x() == 1.2f);
        REQUIRE(point.y() == 3.4f);
    }

    SECTION("setters") {
        auto point = Point();
        point.set_x(1.2f);
        point.set_y(3.4f);
        REQUIRE(point == Point(1.2f, 3.4f));
    }

    SECTION("get()") {
        const auto [x, y] = Point(1.2f, 3.4f);
        REQUIRE(x == 1.2f);
        REQUIRE(y == 3.4f);
    }

    SECTION("format(point, context)") {
        const auto point = Point(1.2f, 3.4f);
        const auto expected = "Point(x: 1.2, y: 3.4)";
        REQUIRE(std::format("{}", point) == expected);
    }

    SECTION("operator+(point, vector)") {
        const auto point = Point(1.2f, 3.4f);
        const auto vector = Vector(5.6f, 7.8f);
        REQUIRE(point + vector == Point(1.2f + 5.6f, 3.4f + 7.8f));
    }

    SECTION("operator+(point, vector)") {
        const auto point = Point(1.2f, 3.4f);
        const auto vector = Vector(5.6f, 7.8f);
        REQUIRE(point - vector == Point(1.2f - 5.6f, 3.4f - 7.8f));
    }
}
