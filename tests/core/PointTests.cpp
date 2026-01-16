#include <tests/catch.hpp>

#include <seraph/core/Math.hpp>
#include <seraph/core/Point.hpp>

TEST_CASE("Point construction", "[Point]") {
    
    SECTION("default Points are constructed with coordinates (0, 0)") {
        const auto point = Point();
        REQUIRE(point.x() == 0.0f);
        REQUIRE(point.y() == 0.0f);
    }

    SECTION("Points can be constructed memberwise") {
        const auto point = Point(1.2f, 3.4f);
        REQUIRE(point.x() == 1.2f);
        REQUIRE(point.y() == 3.4f);
    }

    SECTION("Points can be copied") {
        const auto point = Point(1.2f, 3.4f);
        const auto other = Point(point);
        REQUIRE(other.x() == point.x());
        REQUIRE(other.y() == point.y());
    }
}

TEST_CASE("static Points", "[Point]") {

    SECTION("Point::zero() returns the default Point") {
        REQUIRE(Point::zero() == Point());
    }
}

TEST_CASE("Point comparison", "[Point]") {

    SECTION("Points can be checked for equality") {
        REQUIRE(Point() == Point(0.0f, 0.0f));
        REQUIRE(Point(1.2f, 3.4f) == Point(1.2f, 3.4f));
    }

    SECTION("Points can be checked for non-equality") {
        REQUIRE(Point() != Point(1.2f, 3.4f));
        REQUIRE(Point(1.2f, 3.4f) != Point(3.4f, 1.2f));
    }

    SECTION("Points can be compared memberwise in the order x, y") {
        REQUIRE(Point(1.2f, 3.4f) < Point(3.4f, 5.6f));
        REQUIRE(Point(3.4f, 1.2f) > Point(1.2f, 3.4f));
    }
}

TEST_CASE("setting Point members after construction", "[Point]") {

    auto point = Point();

    SECTION("x can be set") {
        point.set_x(1.2f);
        REQUIRE(point.x() == 1.2f);
    }

    SECTION("y can be set") {
        point.set_y(3.4f);
        REQUIRE(point.y() == 3.4f);
    }
}

TEST_CASE("Point structured bindings", "[Point]") {

    SECTION("Points support structured bindings") {
        const auto point = Point(1.2f, 3.4f);
        const auto &[x, y] = point;
        REQUIRE(x == 1.2f);
        REQUIRE(y == 3.4f);
    }
}

TEST_CASE("Point arithmetic", "[Point]") {

    SECTION("Points can be multiplied by a floating-point value") {
        REQUIRE((Point(1.2f, 3.4f) * 5.6f).is_approximately(Point(6.72f, 19.04f)));
    }
}
    