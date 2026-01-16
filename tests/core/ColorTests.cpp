#include <tests/catch.hpp>

#include <seraph/core/Color.hpp>

TEST_CASE("Color construction", "[Color]") {
    
    SECTION("default Colors are the color black") {
        REQUIRE(Color() == Color::black());
    }

    SECTION("Colors can be constructed memberwise") {
        const auto color = Color(1, 2, 3, 4);
        REQUIRE(color.r() == 1);
        REQUIRE(color.g() == 2);
        REQUIRE(color.b() == 3);
        REQUIRE(color.a() == 4);
    }

    SECTION("Colors can be constructed with the alpha argument omitted") {
        const auto color = Color(1, 2, 3);
        REQUIRE(color.r() == 1);
        REQUIRE(color.g() == 2);
        REQUIRE(color.b() == 3);
        REQUIRE(color.a() == 255);
    }

    SECTION("Colors can be copied") {
        const auto color = Color(1, 2, 3, 4);
        const auto other = Color(color);
        REQUIRE(other.r() == color.r());
        REQUIRE(other.g() == color.g());
        REQUIRE(other.b() == color.b());
        REQUIRE(other.a() == color.a());
    }
}

TEST_CASE("static Colors", "[Color]") {

    SECTION("Color::black() returns the color black") {
        REQUIRE(Color::black() == Color(0, 0, 0, 255));
    }

    SECTION("Color::red() returns the color red") {
        REQUIRE(Color::red() == Color(255, 0, 0, 255));
    }

    SECTION("Color::green() returns the color green") {
        REQUIRE(Color::green() == Color(0, 255, 0, 255));
    }

    SECTION("Color::blue() returns the color blue") {
        REQUIRE(Color::blue() == Color(0, 0, 255, 255));
    }

    SECTION("Color::yellow() returns the color yellow") {
        REQUIRE(Color::yellow() == Color(255, 255, 0, 255));
    }

    SECTION("Color::cyan() returns the color cyan") {
        REQUIRE(Color::cyan() == Color(0, 255, 255, 255));
    }

    SECTION("Color::magenta() returns the color magenta") {
        REQUIRE(Color::magenta() == Color(255, 0, 255, 255));
    }

    SECTION("Color::white() returns the color white") {
        REQUIRE(Color::white() == Color(255, 255, 255, 255));
    }

    SECTION("Color::transparent() returns the color black with a zeroed alpha component") {
        REQUIRE(Color::transparent() == Color(0, 0, 0, 0));
    }
}

TEST_CASE("Color comparison", "[Color]") {

    SECTION("Colors can be checked for equality") {
        REQUIRE(Color() == Color(0, 0, 0, 255));
        REQUIRE(Color::red() == Color(255, 0, 0, 255));
    }

    SECTION("Colors can be checked for non-equality") {
        REQUIRE(Color() != Color::blue());
        REQUIRE(Color::black() != Color::transparent());
    }

    SECTION("Colors can be compared memberwise in the order r, g, b, a") {
        REQUIRE(Color(0, 255, 255, 255) < Color(255, 0, 0, 0));
        REQUIRE(Color(0, 255, 0, 0) > Color(0, 128, 0, 0));
    }
}

TEST_CASE("setting Color members after construction", "[Color]") {

    auto color = Color();

    SECTION("r can be set") {
        color.set_r(128);
        REQUIRE(color.r() == 128);
    }

    SECTION("g can be set") {
        color.set_g(128);
        REQUIRE(color.g() == 128);
    }

    SECTION("b can be set") {
        color.set_b(128);
        REQUIRE(color.b() == 128);
    }

    SECTION("a can be set") {
        color.set_a(128);
        REQUIRE(color.a() == 128);
    }
}

TEST_CASE("Color structured bindings", "[Color]") {

    SECTION("Colors support structured bindings") {
        const auto color = Color(1, 2, 3, 4);
        const auto &[r, g, b, a] = color;
        REQUIRE(r == 1);
        REQUIRE(g == 2);
        REQUIRE(b == 3);
        REQUIRE(a == 4);
    }
}
    