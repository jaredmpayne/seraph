#include <tests/catch.hpp>

#include <seraph/core/Math.hpp>
#include <seraph/core/Size.hpp>

TEST_CASE("Size construction", "[Size]") {
    
    SECTION("default Sizes are constructed with coordinates (0, 0)") {
        const auto size = Size();
        REQUIRE(size.width() == 0.0f);
        REQUIRE(size.height() == 0.0f);
    }

    SECTION("Sizes can be constructed memberwise") {
        const auto size = Size(1.2f, 3.4f);
        REQUIRE(size.width() == 1.2f);
        REQUIRE(size.height() == 3.4f);
    }

    SECTION("Sizes can be copied") {
        const auto size = Size(1.2f, 3.4f);
        const auto other = Size(size);
        REQUIRE(other.width() == size.width());
        REQUIRE(other.height() == size.height());
    }
}

TEST_CASE("Size comparison", "[Size]") {

    SECTION("Sizes can be checked for exact equality") {
        REQUIRE(Size() == Size(0.0f, 0.0f));
        REQUIRE(Size(1.2f, 3.4f) == Size(1.2f, 3.4f));
    }

    SECTION("Sizes can be checked for exact non-equality") {
        REQUIRE(Size() != Size(1.2f, 3.4f));
        REQUIRE(Size(1.2f, 3.4f) != Size(3.4f, 1.2f));
    }

    SECTION("Sizes can be compared memberwise in the order x, y") {
        REQUIRE(Size(1.2f, 3.4f) < Size(3.4f, 5.6f));
        REQUIRE(Size(3.4f, 1.2f) > Size(1.2f, 3.4f));
    }
}

TEST_CASE("setting Size members after construction", "[Size]") {

    auto size = Size();

    SECTION("width can be set") {
        size.set_width(1.2f);
        REQUIRE(size.width() == 1.2f);
    }

    SECTION("height can be set") {
        size.set_height(3.4f);
        REQUIRE(size.height() == 3.4f);
    }
}

TEST_CASE("Size structured bindings", "[Size]") {

    SECTION("Sizes support structured bindings") {
        const auto size = Size(1.2f, 3.4f);
        const auto &[width, height] = size;
        REQUIRE(width == 1.2f);
        REQUIRE(height == 3.4f);
    }
}

TEST_CASE("Size arithmetic", "[Size]") {

    SECTION("Sizes can be multiplied by a floating-point value") {
        REQUIRE((Size(1.2f, 3.4f) * 5.6f).is_approximately(Size(6.72f, 19.04f)));
    }
}
    