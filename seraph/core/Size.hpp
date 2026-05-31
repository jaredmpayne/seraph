#pragma once

#include <format>
#include <iostream>
#include <tuple>
#include <utility>

#include <seraph/core/Math.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/hash/SipHasher.hpp>

class Size {

public:

    /// Constructs a `Size` of zero width and height.
    constexpr Size() noexcept = default;

    /// Constructs a `Size` with the given width and height.
    constexpr Size(float width, float height) noexcept :
        m_width(width),
        m_height(height) { }

    /// Moves a `Size` from another.
    constexpr Size(Size &&) noexcept = default;

    /// Copies a `Size` from another.
    constexpr Size(const Size &) noexcept = default;

    /// Move assigns a `Size` from another.
    constexpr Size &operator=(Size &&) noexcept = default;

    /// Copy assigns a `Size` from another.
    constexpr Size &operator=(const Size &) noexcept = default;

    /// Compares two `Size` objects.
    ///
    /// The objects are effectively compared as tuples `(width(), height())`.
    constexpr auto operator<=>(const Size &other) const noexcept = default;

    /// Returns the width of the `Size`.
    constexpr float width() const noexcept {
        return m_width;
    }

    /// Sets the width of the `Size`.
    void set_width(float width) noexcept {
        m_width = width;
    }

    /// Returns the height of the `Size`.
    constexpr float height() const noexcept {
        return m_height;
    }

    /// Sets the height of the `Size`.
    void set_height(float height) noexcept {
        m_height = height;
    }

    /// Tests the `Size` for approximate equivalency with another.
    ///
    /// @param other The other `Size`.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    constexpr bool is_approximately(const Size &other, float tolerance = Math::epsilon()) const noexcept {
        return Math::is_approximately(width(), other.width(), tolerance)
            && Math::is_approximately(height(), other.height(), tolerance);
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Size> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_width;
        }
        if constexpr (Index == 1) {
            return m_height;
        }
        std::unreachable();
    }

private:

    float m_width;

    float m_height;
};

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Size> : tuple_element<Index, tuple<float, float>> { };

    template <>
    struct tuple_size<Size> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Size> {

        size_t operator()(const Size &size) const noexcept {
            auto hasher = SipHasher();
            hasher.write(size);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Size> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        format_context::iterator format(const Size &size, format_context &context) const noexcept {
            const auto [width, height] = size;
            return format_to(context.out(), "Size(width: {}, height: {})", width, height);
        };
    };

    inline ostream &operator<<(ostream &stream, const Size &size) noexcept {
        return stream << format("{}", size);
    }
}

constexpr Size operator+(const Size &size, const Vector &vector) noexcept {
    return Size(size.width() + vector.dx(), size.height() + vector.dy());
}

constexpr Size operator+(const Size &size, const Size &other) noexcept {
    return size + Vector(other.width(), other.height());
}

constexpr Size operator+(const Size &size, float magnitude) noexcept {
    return size + Size(magnitude, magnitude);
}

constexpr Size operator-(const Size &size) noexcept {
    return Size(-size.width(), -size.height());
}

constexpr Size operator-(const Size &size, const Size &other) noexcept {
    return Size(size.width() - other.width(), size.height() - other.height());
}

constexpr Size operator*(const Size &size, float magnitude) noexcept {
    return Size(magnitude * size.width(), magnitude * size.height());
}

constexpr Size operator*(float magnitude, const Size &size) noexcept {
    return size * magnitude;
}

constexpr Size operator/(const Size &size, float magnitude) noexcept {
    return Size(size.width() / magnitude, size.height() / magnitude);
}

constexpr Size &operator+=(Size &size, const Size &other) noexcept {
    size = size + other;
    return size;
}

constexpr Size &operator-=(Size &size, const Size &other) noexcept {
    size = size - other;
    return size;
}

constexpr Size &operator*=(Size &size, float magnitude) noexcept {
    size = size * magnitude;
    return size;
}

constexpr Size &operator/=(Size &size, float magnitude) noexcept {
    size = size / magnitude;
    return size;
}
