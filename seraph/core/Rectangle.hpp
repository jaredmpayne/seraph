#pragma once

#include <array>
#include <iostream>
#include <tuple>
#include <utility>

#include <seraph/core/Math.hpp>
#include <seraph/core/Point.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/hash/SipHasher.hpp>

/// A primitive class comprised of a `Point` in space and a `Size` width and height.
class Rectangle {

public:

    /// Constructs a `Rectangle` of zero width and height centered at the origin.
    constexpr Rectangle() noexcept = default;

    /// Constructs a `Rectangle` of the given position and size.
    constexpr Rectangle(const Point &position, const Size &size) noexcept :
        m_position(position),
        m_size(size) { }
    
    /// Constructs a `Rectangle` at position *(x, y)* of the given width and
    /// height.
    ///
    /// Effectively an alias for `Rectangle(Point(x, y), Size(width, height))`.
    constexpr Rectangle(float x, float y, float width, float height) noexcept :
        Rectangle(Point(x, y), Size(width, height)) { }

    /// Moves a `Point` from another.
    constexpr Rectangle(Rectangle &&) noexcept = default;

    /// Copies a `Point` from another.
    constexpr Rectangle(const Rectangle &) noexcept = default;

    /// Assigns a `Point` from another.
    constexpr Rectangle &operator=(const Rectangle &) noexcept = default;

    /// Compares two `Point` objects.
    ///
    /// The objects are effectively compared as tuples `(position(), size())`.
    constexpr auto operator<=>(const Rectangle &) const noexcept = default;

    /// Constructs and returns a `Rectangle` of the given size whose top left
    /// corner is at the given point.
    constexpr static Rectangle from_top_left_corner(const Point &point, const Size &size) noexcept {
        return from_top_left_corner(point.x(), point.y(), size.width(), size.height());
    }

    /// Constructs and returns a `Rectangle` of the given width and height
    /// whose top left corner is at the given *x* and *y* coordinates.
    ///
    /// Effectively an alias for `Rectangle::from_top_left_corner(Point(
    /// x + 0.5f * width, y + 0.5f * height), Size(width, height))`.
    constexpr static Rectangle from_top_left_corner(float x, float y, float width, float height) noexcept {
        return Rectangle(Point(x + 0.5f * width, y + 0.5f - height), Size(width, height));
    }

    /// Returns the position of the `Rectangle`.
    constexpr const Point &position() const noexcept {
        return m_position;
    }

    /// @copydoc Rectangle::position() const
    Point &position() noexcept {
        return m_position;
    }

    /// Sets the position of the `Rectangle`.
    void set_position(const Point &position) noexcept {
        m_position = position;
    }

    /// Returns the *x* coordinate of the `Rectangle`.
    ///
    /// Effectively an alias for `position().x()`.
    constexpr float x() const noexcept {
        return position().x();
    }

    /// Sets the *x* coordinate of the `Rectangle`.
    ///
    /// Effectively an alias for `position().set_x(x)`.
    void set_x(float x) noexcept {
        position().set_x(x);
    }

    /// Returns the *y* coordinate of the `Rectangle`.
    ///
    /// Effectively an alias for `position().y()`.
    constexpr float y() const noexcept {
        return position().y();
    }

    /// Sets the *y* coordinate of the `Rectangle`.
    ///
    /// Effectively an alias for `position().set_y(y)`.
    void set_y(float y) noexcept {
        position().set_y(y);
    }

    /// Returns the size of the `Rectangle`.
    constexpr const Size &size() const noexcept {
        return m_size;
    }

    /// @copydoc Rectangle::size() const
    Size &size() noexcept {
        return m_size;
    }

    /// Sets the size of the `Rectangle`.
    void set_size(const Size &size) noexcept {
        m_size = size;
    }

    /// Returns the width of the `Rectangle`.
    ///
    /// Effectively an alias for `size().width()`.
    constexpr float width() const noexcept {
        return size().width();
    }

    /// Sets the width of the `Rectangle`.
    ///
    /// Effectively an alias for `size().set_width(width)`.
    void set_width(float width) noexcept {
        size().set_width(width);
    }

    /// Returns the height of the `Rectangle`.
    ///
    /// Effectively an alias for `size().height()`.
    constexpr float height() const noexcept {
        return size().height();
    }

    /// Sets the height of the `Rectangle`.
    ///
    /// Effectively an alias for `size().set_height(height)`.
    void set_height(float height) noexcept {
        m_size.set_height(height);
    }

    constexpr float min_x() const noexcept {
        return x() - 0.5f * width();
    }

    constexpr float max_x() const noexcept {
        return x() + 0.5f * width();
    }

    constexpr float min_y() const noexcept {
        return y() - 0.5f * height();
    }

    constexpr float max_y() const noexcept {
        return y() + 0.5f * height();
    }

    constexpr float area() const noexcept {
        return width() * height();
    }

    constexpr Point top_left_corner() const noexcept {
        return Point(min_x(), min_y());
    }

    constexpr Point top_left_corner(float rotation) const noexcept {
        if (rotation == 0.0f) {
            return top_left_corner();
        }
        const auto sin_r = std::sin(rotation);
        const auto cos_r = std::cos(rotation);
        return Point(
            x() - (0.5f * width() * cos_r - 0.5f * height() * sin_r),
            y() - (0.5f * width() * sin_r - 0.5f * height() * cos_r)
        );
    }

    constexpr Point top_right_corner() const noexcept {
        return Point(max_x(), min_y());
    }

    constexpr Point top_right_corner(float rotation) const noexcept {
        if (rotation == 0.0f) {
            return top_right_corner();
        } 
        const auto sin_r = std::sin(rotation);
        const auto cos_r = std::cos(rotation);
        return Point(
            x() + (0.5f * width() * cos_r - 0.5f * height() * sin_r),
            y() + (0.5f * width() * sin_r + 0.5f * height() * cos_r)
        );
    }

    constexpr Point bottom_left_corner() const noexcept {
        return Point(min_x(), max_y());
    }

    constexpr Point bottom_left_corner(float rotation) const noexcept {
        if (rotation == 0.0f) {
            return top_left_corner();
        }
        const auto sin_r = std::sin(rotation);
        const auto cos_r = std::cos(rotation);
        return Point(
            x() - (0.5f * width() * cos_r + 0.5f * height() * sin_r),
            y() - (0.5f * width() * sin_r - 0.5f * height() * cos_r)
        );
    }

    constexpr Point bottom_right_corner() const noexcept {
        return Point(max_x(), max_y());
    }

    constexpr Point bottom_right_corner(float rotation) const noexcept {
        if (rotation == 0.0f) {
            return top_left_corner();
        }
        const auto sin_r = std::sin(rotation);
        const auto cos_r = std::cos(rotation);
        return Point(
            x() + (0.5f * width() * cos_r + 0.5f * height() * sin_r),
            y() + (0.5f * width() * sin_r - 0.5f * height() * cos_r)
        );
    }

    constexpr Vector top_edge(float rotation) const noexcept {
        if (rotation) {
            const auto tl = top_left_corner(rotation);
            const auto tr = top_right_corner(rotation);
            return Vector(tr.x() - tl.x(), tr.y() - tl.y());
        }
        return Vector(max_x() - min_x(), 0.0f);
    }

    constexpr Vector left_edge(float rotation) const noexcept {
        if (rotation) {
            const auto tl = top_left_corner(rotation);
            const auto bl = bottom_left_corner(rotation);
            return Vector(tl.x() - bl.x(), tl.y() - bl.y());
        }
        return Vector(0.0f, min_y() - max_y());
    }

    constexpr Vector right_edge(float rotation) const noexcept {
        if (rotation) {
            const auto tr = top_right_corner(rotation);
            const auto br = bottom_right_corner(rotation);
            return Vector(br.x() - tr.x(), br.y() - tr.y());
        }
        return Vector(0.0f, max_y() - min_y());
    }

    constexpr Vector bottom_edge(float rotation) const noexcept {
        if (rotation) {
            const auto bl = bottom_left_corner(rotation);
            const auto br = bottom_right_corner(rotation);
            return Vector(bl.x() - br.x(), bl.y() - br.y());
        }
        return Vector(min_x() - max_x(), 0.0f);
    }

    /// Tests the `Rectangle` for approximate equivalency with another.
    ///
    /// @param other The other `Rectangle`.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    constexpr bool is_approximately(const Rectangle &other, float tolerance = Math::epsilon()) const noexcept {
        return position().is_approximately(other.position(), tolerance)
            && size().is_approximately(other.size(), tolerance);
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Rectangle> &get() const noexcept {
        if constexpr (Index == 0) {
            return position();
        }
        if constexpr (Index == 1) {
            return size();
        }
        std::unreachable();
    }

private:

    Point m_position;

    Size m_size;
};

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Rectangle> : tuple_element<Index, tuple<Point, Size>> { };

    template <>
    struct tuple_size<Rectangle> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Rectangle> {

        size_t operator()(const Rectangle &rectangle) const noexcept {
            auto hasher = SipHasher();
            hasher.write(rectangle);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Rectangle> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        format_context::iterator format(const Rectangle &rectangle, format_context &context) const noexcept {
            const auto [p, s] = rectangle;
            return format_to(context.out(), "Rectangle(position: {}, size: {})", p, s);
        };
    };

    inline ostream &operator<<(ostream &stream, const Rectangle &rectangle) noexcept {
        return stream << format("{}", rectangle);
    }
}
