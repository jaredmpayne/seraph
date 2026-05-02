#pragma once

#include <cmath>
#include <format>
#include <iostream>
#include <numeric>
#include <tuple>

#include <seraph/core/Math.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/hash/SipHasher.hpp>

/// Represents a two-dimensional point in space.
class Point {

public:

    /// Constructs a `Point` centered at the origin.
    constexpr Point() noexcept = default;

    /// Constructs a `Point` with the given coordinates.
    constexpr Point(float x, float y) noexcept :
        m_x(x),
        m_y(y) { }

    /// Moves a `Point` from another.
    constexpr Point(Point &&) noexcept = default;

    /// Copies a `Point` from another.
    constexpr Point(const Point &) noexcept = default;

    /// Assigns a `Point` from another.
    constexpr Point &operator=(const Point &) noexcept = default;

    /// Compares two `Point` objects.
    ///
    /// The objects are effectively compared as tuples `(x(), y())`.
    constexpr auto operator<=>(const Point &) const noexcept = default;

    /// Returns a `Point` centered at the origin.
    ///
    /// Effectively an alias for `Point()`.
    static constexpr Point zero() noexcept {
        return Point();
    }

    /// Returns the *x* coordinate of the `Point`.
    constexpr float x() const noexcept {
        return m_x;
    }

    /// Sets the *x* coordinate of the `Point`.
    void set_x(float x) noexcept {
        m_x = x;
    }

    /// Returns the *y* coordinate of the `Point`.
    constexpr float y() const noexcept {
        return m_y;
    }

    /// Sets the *y* coordinate of the `Point`.
    void set_y(float y) noexcept {
        m_y = y;
    }

    /// Returns the angle in radians from this `Point` to another.
    constexpr float angle(const Point &other) const noexcept {
        return std::atan2(y() - other.y(), x() - other.x());
    }

    /// Returns the distance from this `Point` to another.
    constexpr float distance(const Point &other) const noexcept {
        return std::hypot(other.x() - x(), other.y() - y());
    }

    /// Returns the midpoint between this `Point` and another.
    constexpr Point midpoint(const Point &other) const noexcept {
        return Point(std::midpoint(x(), other.x()), std::midpoint(y(), other.y()));
    }

    /// Tests the `Point` for approximate equivalency with another.
    ///
    /// @param other The other `Point`.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    constexpr bool is_approximately(const Point &other, float tolerance = Math::epsilon()) const noexcept {
        return Math::is_approximately(x(), other.x(), tolerance)
            && Math::is_approximately(y(), other.y(), tolerance);
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Point> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_x;
        }
        if constexpr (Index == 1) {
            return m_y;
        }
        std::unreachable();
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

        size_t operator()(const Point &point) const noexcept {
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

        format_context::iterator format(const Point &point, format_context &context) const noexcept {
            const auto [x, y] = point;
            return format_to(context.out(), "Point(x: {}, y: {})", x, y);
        };
    };

    inline ostream &operator<<(ostream &stream, const Point &point) noexcept {
        return stream << format("{}", point);
    }
}

constexpr Point operator+(const Point &point, const Point &other) noexcept {
    return Point(point.x() + other.x(), point.y() + other.y());
}

constexpr Point operator+(const Point &point, const Vector &vector) noexcept {
    return point + Point(vector.dx(), vector.dy());
}

constexpr Point operator+(const Vector &vector, const Point &point) noexcept {
    return Point(vector.dx(), vector.dy()) + point;
}

constexpr Point operator+(const Point &point, float magnitude) noexcept {
    return point + Point(magnitude, magnitude);
}

constexpr Point operator+(float magnitude, const Point &point) noexcept {
    return Point(magnitude, magnitude) + point;
}

constexpr Point operator-(const Point &point) noexcept {
    return Point(-point.x(), -point.y());
}

constexpr Point operator-(const Point &point, const Point &other) noexcept {
    return Point(point.x() - other.x(), point.y() - other.y());
}

constexpr Point operator-(const Point &point, const Vector &vector) noexcept {
    return point - Point(vector.dx(), vector.dy());
}

constexpr Point operator-(const Point &point, float magnitude) noexcept {
    return point - Point(magnitude, magnitude);
}

constexpr Point operator-(float magnitude, const Point &point) noexcept {
    return Point(magnitude, magnitude) - point;
}

constexpr Point operator*(const Point &point, const Point &other) noexcept {
    return Point(point.x() * other.x(), point.y() * other.y());
}

constexpr Point operator*(const Point &point, const Vector &vector) noexcept {
    return point * Point(vector.dx(), vector.dy());
}

constexpr Point operator*(const Point &point, float magnitude) noexcept {
    return point * Point(magnitude, magnitude);
}

constexpr Point operator*(float magnitude, const Point &point) noexcept {
    return Point(magnitude, magnitude) * point;
}

constexpr Point operator/(const Point &point, const Point &other) noexcept {
    return Point(point.x() / other.x(), point.y() / other.y());
}

constexpr Point operator/(const Point &point, const Vector &vector) noexcept {
    return point / Point(vector.dx(), vector.dy());
}

constexpr Point operator/(const Point &point, float magnitude) noexcept {
    return point / Point(magnitude, magnitude);
}

constexpr Point operator/(float magnitude, const Point &point) noexcept {
    return Point(magnitude, magnitude) / point;
}

constexpr Point &operator+=(Point &point, const Point &other) noexcept {
    point = point + other;
    return point;
}

constexpr Point &operator-=(Point &point, const Point &other) noexcept {
    point = point - other;
    return point;
}

constexpr Point &operator*=(Point &point, float magnitude) noexcept {
    point = point * magnitude;
    return point;
}

constexpr Point &operator/=(Point &point, float magnitude) noexcept {
    point = point / magnitude;
    return point;
}
