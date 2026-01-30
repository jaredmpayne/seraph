#pragma once

#include <numbers>

#include <seraph/core/Point.hpp>
#include <seraph/hash/SipHasher.hpp>

/// A class comprised of a `Point` in space and a floating-point radius.
class Circle {

public:

    /// Constructs a `Circle` with a zeroed position and zero radius.
    constexpr Circle() noexcept = default;

    /// Constructs a `Circle` with at `positon` with given `radius`.
    constexpr Circle(const Point &position, float radius) noexcept :
        m_position(position),
        m_radius(radius) { }

    /// Constructs a `Circle` with position *(x, y)* with given `radius`.
    ///
    /// Effectively an alias for `Circle(Position(x, y), radius)`.
    constexpr Circle(float x, float y, float radius) noexcept :
        Circle(Point(x, y), radius) { }

    /// Moves a `Circle` from another.
    constexpr Circle(Circle &&) noexcept = default;

    /// Copies a `Circle` from another.
    constexpr Circle(const Circle &) noexcept = default;

    /// Assigns a `Circle` from another.
    constexpr Circle &operator=(const Circle &) noexcept = default;

    /// Compares two `Circle` objects.
    ///
    /// The objects are effectively compared as tuples `(position(), radius())`.
    constexpr auto operator<=>(const Circle &) const noexcept = default;

    /// The `Point` representing the center of the `Circle`.
    constexpr const Point &position() const noexcept {
        return m_position;
    }

    /// @copydoc Circle::position() const
    Point &position() noexcept {
        return m_position;
    }

    /// Sets the `Point` position of the `Circle`.
    void set_position(const Point &position) noexcept {
        m_position = position;
    }

    /// Returns the `Circle`'s *x* coordinate.
    ///
    /// Effectively an alias for `position().x()`.
    constexpr float x() const noexcept {
        return position().x();
    }

    /// Sets the `Circle`'s *x* coordinate.
    ///
    /// Effectively an alias for `position().set_x(x)`.
    void set_x(float x) noexcept {
        position().set_x(x);
    }

    /// Returns the `Circle`'s *y* coordinate.
    ///
    /// Effectively an alias for `position().y()`.
    constexpr float y() const noexcept {
        return position().y();
    }

    /// Sets the `Circle`'s *y* coordinate.
    ///
    /// Effectively an alias for `position().set_y(y)`.
    void set_y(float y) noexcept {
        position().set_y(y);
    }

    /// Returns the radius of the `Circle`.
    constexpr float radius() const noexcept {
        return m_radius;
    }

    /// Sets the radius of the `Circle`.
    void set_radius(float radius) noexcept {
        m_radius = radius;
    }

    /// Tests the `Circle` for approximate equivalency with another.
    ///
    /// @param other The other `Circle`.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    constexpr bool is_approximately(const Circle &other, float tolerance = Math::epsilon()) const noexcept {
        return position().is_approximately(other.position(), tolerance)
            && Math::is_approximately(radius(), other.radius(), tolerance);
    }

    /// Returns the diameter of the `Circle`.
    constexpr float diameter() const noexcept {
        return 2 * radius();
    }

    /// Returns the area of the `Circle`.
    constexpr float area() const noexcept {
        return std::numbers::pi_v<float> * radius() * radius();
    }

    /// Returns the leftmost *x* coordinate of the `Circle` in space.
    constexpr float min_x() const noexcept {
        return x() - radius();
    }

    /// Returns the rightmost *x* coordinate of the `Circle` in space.
    constexpr float max_x() const noexcept {
        return x() + radius();
    }

    /// Returns the uppermost *y* coordinate of the `Circle` in space.
    constexpr float min_y() const noexcept {
        return y() - radius();
    }

    /// Returns the lowermost *y* coordinate of the `Circle` in space.
    constexpr float max_y() const noexcept {
        return y() + radius();
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Circle> &get() const noexcept {
        if constexpr (Index == 0) {
            return position();
        } 
        if constexpr (Index == 1) {
            return radius();
        }
    }

private:

    Point m_position;

    float m_radius;
};

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Circle> : tuple_element<Index, tuple<Point, float>> { };

    template <>
    struct tuple_size<Circle> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Circle> {

        size_t operator()(const Circle &circle) const noexcept {
            auto hasher = SipHasher();
            hasher.write(circle);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Circle> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        format_context::iterator format(const Circle &circle, format_context &context) const noexcept {
            const auto &[p, r] = circle;
            return format_to(context.out(), "Circle(position: {}, radius: {})", p, r);
        };
    };

    inline ostream &operator<<(ostream &stream, const Circle &circle) noexcept {
        return stream << format("{}", circle);
    }
}
