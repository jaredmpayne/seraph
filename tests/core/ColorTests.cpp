#include <tests/catch.hpp>

#include <seraph/core/Color.hpp>

TEST_CASE("Color", "[Color]") {
    
    SECTION("Color()") {
        const auto color = Color();
        REQUIRE(color == Color(0, 0, 0, 255));
    }

    SECTION("Color(r, g, b)") {
        const auto color = Color(1, 2, 3);
        REQUIRE(color == Color(1, 2, 3, 255));
    }

    SECTION("Color(r, g, b, a)") {
        const auto color = Color(4, 5, 6, 7);
        REQUIRE(color == Color(4, 5, 6, 7));
    }

    SECTION("Color(other)") {
        const auto color = Color(1, 2, 3, 4);
        const auto other = Color(color);
        REQUIRE(color == other);
    }

    SECTION("operator<=>(other)") {
        const auto small = Color(1, 2, 3, 4);
        const auto large = Color(5, 6, 7, 8);
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

    SECTION("black()") {
        REQUIRE(Color::black() == Color(0, 0, 0, 255));
    }

    SECTION("red()") {
        REQUIRE(Color::red() == Color(255, 0, 0, 255));
    }

    SECTION("green()") {
        REQUIRE(Color::green() == Color(0, 255, 0, 255));
    }

    SECTION("blue()") {
        REQUIRE(Color::blue() == Color(0, 0, 255, 255));
    }

    SECTION("yellow()") {
        REQUIRE(Color::yellow() == Color(255, 255, 0, 255));
    }

    SECTION("cyan()") {
        REQUIRE(Color::cyan() == Color(0, 255, 255, 255));
    }

    SECTION("magenta()") {
        REQUIRE(Color::magenta() == Color(255, 0, 255, 255));
    }

    SECTION("white()") {
        REQUIRE(Color::white() == Color(255, 255, 255, 255));
    }

    SECTION("transparent()") {
        REQUIRE(Color::transparent() == Color(0, 0, 0, 0));
    }

    SECTION("getters") {
        const auto color = Color(1, 2, 3, 4);
        REQUIRE(color.r() == 1);
        REQUIRE(color.g() == 2);
        REQUIRE(color.b() == 3);
        REQUIRE(color.a() == 4);
    }

    SECTION("setters") {
        auto color = Color();
        color.set_r(1);
        color.set_g(2);
        color.set_b(3);
        color.set_a(4);
        REQUIRE(color == Color(1, 2, 3, 4));
    }

    SECTION("get()") {
        const auto [r, g, b, a] = Color(1, 2, 3, 4);
        REQUIRE(r == 1);
        REQUIRE(g == 2);
        REQUIRE(b == 3);
        REQUIRE(a == 4);
    }
    
    SECTION("format(color, context)") {
        const auto color = Color(1, 2, 3, 4);
        const auto expected = "Color(r: 1, g: 2, b: 3, a: 4)";
        REQUIRE(std::format("{}", color) == expected);
    }
}
