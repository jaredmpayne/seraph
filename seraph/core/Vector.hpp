#pragma once

#include <compare>
#include <format>
#include <iostream>
#include <tuple>

#include <seraph/hash/SipHasher.hpp>

/// Represents a magnitude in 2-D space.
class Vector {

public:

    /// Constructs a `Vector` with zero magnitude.
    constexpr Vector() noexcept = default;

    constexpr Vector(Vector &&) noexcept = default;

    constexpr Vector(const Vector &) noexcept = default;

    constexpr Vector &operator=(const Vector &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Vector &) const noexcept = default;

    /// Constructs a `Vector` with the given *dx* and *dy* magnitudes.
    constexpr Vector(float dx, float dy) noexcept :
        m_dx(dx),
        m_dy(dy) { }

    /// Returns a `Vector` of zero magnitude.
    ///
    /// Specifically, the `Vector` is of value (0.0, 0.0).
    static constexpr Vector zero() noexcept {
        return Vector(0.0f, 0.0f);
    }

    /// Returns a `Vector` of identity in the *x* and *y* direction.
    ///
    /// Specifically, the `Vector` is of value (1.0, 1.0).
    static constexpr Vector one() noexcept {
        return Vector(1.0f, 1.0f);
    }

    static constexpr Vector up() noexcept {
        return Vector(0.0f, -1.0f);
    }

    static constexpr Vector down() noexcept {
        return Vector(0.0f, 1.0f);
    }

    static constexpr Vector left() noexcept {
        return Vector(-1.0f, 0.0f);
    }

    static constexpr Vector right() noexcept {
        return Vector(1.0f, 0.0f);
    }

    constexpr float dx() const noexcept {
        return m_dx;
    }

    inline void set_dx(float dx) noexcept {
        m_dx = dx;
    }

    constexpr float dy() const noexcept {
        return m_dy;
    }

    inline void set_dy(float dy) noexcept {
        m_dy = dy;
    }

    /// Returns the Euclidean magnitude of the `Vector`.
    constexpr float magnitude() const noexcept {
        return std::hypot(dx(), dy());
    }

    /// Returns the equivalent `Vector` perpendicular to the caller.
    constexpr Vector perpendicular() const noexcept {
        return Vector(-1.0f * dy(), dx());
    }

    /// Returns the normalized magnitude of the caller.
    constexpr Vector normalized() const noexcept {
        const auto m = magnitude();
        return Vector(dx() / m, dy() / m);
    }

    constexpr float dot_product(const Vector &other) const noexcept {
        return dx() * other.dx() + dy() * other.dy();
    }

    template <typename std::size_t Index>
    constexpr const std::tuple_element_t<Index, Vector> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_dx;
        }
        if constexpr (Index == 1) {
            return m_dy;
        }
    }

    /// Multiplies a `Vector` by a given magnitude.
    ///
    /// Effectively multiplies the `Vector`'s *dx* and *dy* magnitudes by
    /// the given magnitude.
    constexpr Vector operator*(float magnitude) const noexcept {
        return Vector(dx() * magnitude, dy() * magnitude);
    }

    constexpr const Vector &operator*=(float magnitude) noexcept {
        *this = *this * magnitude;
        return *this;
    }

    /// Multiplies a `Vector` by the given `Vector`.
    ///
    /// Effectively multiplies the `Vector`'s *dx* and *dy* magnitudes by
    /// the given `Vector`'s *dx* and *dy* magnitudes respectively.
    constexpr Vector operator*(const Vector &other) const noexcept {
        return Vector(dx() * other.dx(), dy() * other.dy());
    }

    constexpr const Vector &operator*=(const Vector &other) noexcept {
        *this = *this * other;
        return *this;
    }

    constexpr Vector operator/(float magnitude) const noexcept {
        return Vector(dx() / magnitude, dy() / magnitude);
    }

    constexpr const Vector &operator/=(float magnitude) noexcept {
        *this = *this / magnitude;
        return *this;
    }

    constexpr Vector operator+(const Vector &other) const noexcept {
        return Vector(dx() + other.dx(), dy() + other.dy());
    }

    constexpr const Vector &operator+=(const Vector &other) noexcept {
        *this = *this + other;
        return *this;
    }

    constexpr Vector operator-(const Vector &other) const noexcept {
        return Vector(dx() - other.dx(), dy() - other.dy());
    }

    constexpr const Vector &operator-=(const Vector &other) noexcept {
        *this = *this - other;
        return *this;
    }

private:

    float m_dx;

    float m_dy;
};

constexpr Vector operator*(float magnitude, const Vector &vector) noexcept {
    return vector * magnitude;
}

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Vector> : tuple_element<Index, tuple<float, float>> { };

    template <>
    struct tuple_size<Vector> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Vector> {

        inline size_t operator()(const Vector &vector) const noexcept {
            auto hasher = SipHasher();
            hasher.write(vector);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Vector> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        inline format_context::iterator format(const Vector &vector, format_context &context) const noexcept {
            const auto [dx, dy] = vector;
            return format_to(context.out(), "Vector(dx: {}, dy: {})", dx, dy);
        };
    };

    inline ostream &operator<<(ostream &stream, const Vector &vector) noexcept {
        return stream << format("{}", vector);
    }
}
