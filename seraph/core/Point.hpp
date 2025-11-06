#pragma once

#include <cmath>
#include <compare>
#include <format>
#include <iostream>
#include <numeric>
#include <tuple>

#include <seraph/core/Vector.hpp>
#include <seraph/hash/SipHasher.hpp>

/// Represents a 2-D point in space.
class Point {

public:

    /// Constructs a `Point` centered at the origin.
    constexpr Point() noexcept = default;

    constexpr Point(Point &&) noexcept = default;

    constexpr Point(const Point &) noexcept = default;

    constexpr Point &operator=(const Point &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Point &) const noexcept = default;

    /// Constructs a `Point` with the given coordinates.
    constexpr Point(float x, float y) noexcept :
        m_x(x),
        m_y(y) { }

    /// Returns a `Point` centered at the origin.
    static constexpr Point zero() noexcept {
        return Point();
    }

    constexpr float x() const noexcept {
        return m_x;
    }

    inline void set_x(float x) noexcept {
        m_x = x;
    }

    constexpr float y() const noexcept {
        return m_y;
    }

    inline void set_y(float y) noexcept {
        m_y = y;
    }

    /// Calculates the angle in radians from this `Point` to another.
    constexpr float angle(const Point &other) const noexcept {
        return std::atan2(y() - other.y(), x() - other.x());
    }

    /// Calculates the distance from this `Point` to another.
    constexpr float distance(const Point &other) const noexcept {
        return std::hypot(other.x() - x(), other.y() - y());
    }

    /// Calculates the midpoint between this `Point` and another.
    constexpr Point midpoint(const Point &other) const noexcept {
        return Point(std::midpoint(x(), other.x()), std::midpoint(y(), other.y()));
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Point> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_x;
        }
        if constexpr (Index == 1) {
            return m_y;
        }
    }

    constexpr Point operator*(float magnitude) const noexcept {
        return Point(magnitude * x(), magnitude * y());
    }

    constexpr Point operator+(const Point &other) const noexcept {
        return Point(x() + other.x(), y() + other.y());
    }

    constexpr Point operator+(const Vector &vector) const noexcept {
        return *this + Point(vector.dx(), vector.dy());
    }

private:

    float m_x;

    float m_y;
};

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Point> : tuple_element<Index, tuple<float, float>> { };

    template <>
    struct tuple_size<Point> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Point> {

        inline size_t operator()(const Point &point) const noexcept {
            auto hasher = SipHasher();
            hasher.write(point);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Point> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        inline format_context::iterator format(const Point &point, format_context &context) const noexcept {
            const auto [x, y] = point;
            return format_to(context.out(), "Point(x: {}, y: {})", x, y);
        };
    };

    inline ostream &operator<<(ostream &stream, const Point &point) noexcept {
        return stream << format("{}", point);
    }
}
