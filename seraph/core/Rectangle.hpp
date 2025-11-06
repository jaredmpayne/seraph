#pragma once

#include <array>
#include <compare>
#include <iostream>
#include <tuple>

#include <seraph/core/Point.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/hash/SipHasher.hpp>

/// A primitive class comprised of a `Point` in space and a `Size` width and height.
class Rectangle {

public:

    /// Constructs a `Rectangle` of zero width and height centered at the origin.
    constexpr Rectangle() noexcept = default;

    constexpr Rectangle(Rectangle &&) noexcept = default;

    constexpr Rectangle(const Rectangle &) noexcept = default;

    constexpr Rectangle &operator=(const Rectangle &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Rectangle &) const noexcept = default;

    /// Constructs a `Rectangle` of the given position and size.
    constexpr Rectangle(const Point &position, const Size &size) noexcept :
        m_position(position),
        m_size(size) { }

    constexpr Rectangle(float x, float y, float width, float height) noexcept :
        Rectangle(Point(x, y), Size(width, height)) { }

    constexpr static Rectangle from_top_left_corner(const Point &point, const Size &size) noexcept {
        return from_top_left_corner(point.x(), point.y(), size.width(), size.height());
    }

    constexpr static Rectangle from_top_left_corner(float x, float y, float width, float height) noexcept {
        return Rectangle(Point(x + 0.5f * width, y + 0.5f - height), Size(width, height));
    }

    constexpr const Point &position() const noexcept {
        return m_position;
    }

    inline void set_position(const Point &position) noexcept {
        m_position = position;
    }

    constexpr const Size &size() const noexcept {
        return m_size;
    }

    inline void set_size(const Size &size) noexcept {
        m_size = size;
    }

    constexpr float x() const noexcept {
        return position().x();
    }

    inline void set_x(float x) noexcept {
        m_position.set_x(x);
    }

    constexpr float y() const noexcept {
        return position().y();
    }

    inline void set_y(float y) noexcept {
        m_position.set_y(y);
    }

    constexpr float width() const noexcept {
        return size().width();
    }

    inline void set_width(float width) noexcept {
        m_size.set_width(width);
    }

    constexpr float height() const noexcept {
        return size().height();
    }

    inline void set_height(float height) noexcept {
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

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Rectangle> &get() const noexcept {
        if constexpr (Index == 0) {
            return position();
        }
        if constexpr (Index == 1) {
            return size();
        }
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

        inline size_t operator()(const Rectangle &rectangle) const noexcept {
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

        inline format_context::iterator format(const Rectangle &rectangle, format_context &context) const noexcept {
            const auto [p, s] = rectangle;
            return format_to(context.out(), "Rectangle(position: {}, size: {})", p, s);
        };
    };

    inline ostream &operator<<(ostream &stream, const Rectangle &rectangle) noexcept {
        return stream << format("{}", rectangle);
    }
}
