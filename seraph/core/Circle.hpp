#pragma once

#include <compare>
#include <numbers>

#include <seraph/core/Point.hpp>
#include <seraph/hash/SipHasher.hpp>

/// A primitive class comprised of a `Point` in space and a floating-point radius.
class Circle {

public:

    /// Constructs a `Circle` with zeroed position and zero radius.
    constexpr Circle() noexcept = default;

    constexpr Circle(Circle &&) noexcept = default;

    constexpr Circle(const Circle &) noexcept = default;

    constexpr Circle &operator=(const Circle &) noexcept = default;

    /// Compares two `Circle` objects.
    ///
    /// The objects are compared by `position` then `radius`.
    constexpr std::strong_ordering operator<=>(const Circle &) const noexcept = default;

    /// Constructs a `Circle` with `radius` at `position`.
    constexpr Circle(const Point &position, float radius) noexcept :
        m_position(position),
        m_radius(radius) { }

    constexpr Circle(float x, float y, float radius) noexcept :
        Circle(Point(x, y), radius) { }

    /// The `Point` representing the center of the `Circle`.
    constexpr const Point &position() const noexcept {
        return m_position;
    }

    /// Sets the `Point` position of the `Circle`.
    inline void set_position(const Point &position) noexcept {
        m_position = position;
    }

    /// An alias for `position().x()`.
    constexpr float x() const noexcept {
        return position().x();
    }

    /// An alias for `position().set_x()`.
    inline void set_x(float x) noexcept {
        m_position.set_x(x);
    }

    /// An alias for `position().y()`.
    constexpr float y() const noexcept {
        return position().y();
    }

    /// An alias for `position().set_y()`.
    inline void set_y(float y) noexcept {
        m_position.set_y(y);
    }

    /// Gets the radius of the `Circle`.
    constexpr float radius() const noexcept {
        return m_radius;
    }

    /// Sets the radius of the `Circle`.
    inline void set_radius(float radius) noexcept {
        m_radius = radius;
    }

    /// Calculates the diameter of the `Circle`.
    constexpr float diameter() const noexcept {
        return 2 * radius();
    }

    /// Calculates the area of the `Circle`.
    constexpr float area() const noexcept {
        return std::numbers::pi_v<float> * radius() * radius();
    }

    /// Calculates the leftmost x-coordinate of the `Circle` in space.
    constexpr float min_x() const noexcept {
        return x() - radius();
    }

    /// Calculates the rightmost x-coordinate of the `Circle` in space.
    constexpr float max_x() const noexcept {
        return x() + radius();
    }

    /// Calculates the uppermost y-coordinate of the `Circle` in space.
    constexpr float min_y() const noexcept {
        return y() - radius();
    }

    /// @brief Calculates the lowermost y-coordinate of the `Circle` in space.
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

        inline size_t operator()(const Circle &circle) const noexcept {
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

        inline format_context::iterator format(const Circle &circle, format_context &context) const noexcept {
            const auto &[p, r] = circle;
            return format_to(context.out(), "Circle(position: {}, radius: {})", p, r);
        };
    };

    inline ostream &operator<<(ostream &stream, const Circle &circle) noexcept {
        return stream << format("{}", circle);
    }
}
