#pragma once

#include <format>
#include <iostream>
#include <tuple>
#include <utility>

#include <seraph/core/Math.hpp>
#include <seraph/hash/SipHasher.hpp>

/// Represents a magnitude in two-dimensional space.
class Vector {

public:

    /// Constructs a `Vector` of zero magnitude.
    constexpr Vector() noexcept = default;

    /// Constructs a `Vector` with the given *dx* and *dy* magnitudes.
    constexpr Vector(float dx, float dy) noexcept :
        m_dx(dx),
        m_dy(dy) { }

    /// Moves a `Vector` from another.
    constexpr Vector(Vector &&) noexcept = default;

    /// Copies a `Vector` from another.
    constexpr Vector(const Vector &) noexcept = default;

    /// Move assigns a `Vector` from another.
    constexpr Vector &operator=(Vector &&) noexcept = default;

    /// Copy assigns a `Vector` from another.
    constexpr Vector &operator=(const Vector &) noexcept = default;

    /// Compares two `Vector` objects.
    ///
    /// The objects are effectively compared as tuples `(dx(), dy())`.
    constexpr auto operator<=>(const Vector &) const noexcept = default;

    /// Returns a `Vector` of zero magnitude.
    ///
    /// Effectively an alias for `Vector()`.
    static constexpr Vector zero() noexcept {
        return Vector(0.0f, 0.0f);
    }

    /// Returns a `Vector` of identity in the *x* and *y* direction.
    ///
    /// Specifically, returns a `Vector` of value *(1.0, 1.0)*.
    static constexpr Vector one() noexcept {
        return Vector(1.0f, 1.0f);
    }

    /// Returns a `Vector` pointing upward in 2-D space.
    ///
    /// Specifically, returns a `Vector` of value *(0.0, -1.0)*.
    static constexpr Vector up() noexcept {
        return Vector(0.0f, -1.0f);
    }

    /// Returns a `Vector` pointing downward in 2-D space.
    ///
    /// Specifically, returns a `Vector` of value *(0.0, 1.0)*.
    static constexpr Vector down() noexcept {
        return Vector(0.0f, 1.0f);
    }

    /// Returns a `Vector` pointing leftward in 2-D space.
    ///
    /// Specifically, returns a `Vector` of value *(-1.0, 0.0)*.
    static constexpr Vector left() noexcept {
        return Vector(-1.0f, 0.0f);
    }

    /// Returns a `Vector` pointing rightward in 2-D space.
    ///
    /// Specifically, returns a `Vector` of value *(1.0, 0.0)*.
    static constexpr Vector right() noexcept {
        return Vector(1.0f, 0.0f);
    }

    /// Returns the *dx* component of the `Vector`.
    constexpr float dx() const noexcept {
        return m_dx;
    }

    /// Sets the *dx* component of the `Vector`.
    void set_dx(float dx) noexcept {
        m_dx = dx;
    }

    /// Returns the *dy* component of the `Vector`.
    constexpr float dy() const noexcept {
        return m_dy;
    }

    /// Sets the *dy* component of the `Vector`.
    void set_dy(float dy) noexcept {
        m_dy = dy;
    }

    /// Returns the Euclidean magnitude of the `Vector`.
    constexpr float magnitude() const noexcept {
        return std::hypot(dx(), dy());
    }

    /// Returns a `Vector` of equivalent magnitude reverse of the `Vector`.
    constexpr Vector reversed() const noexcept {
        return Vector(-1.0f * dx(), -1.0f * dy());
    }

    /// Returns a `Vector` of equivalent magnitude perpendicular to the `Vector`.
    constexpr Vector perpendicular() const noexcept {
        return Vector(-1.0f * dy(), dx());
    }

    /// Returns a normalized copy of the `Vector`.
    constexpr Vector normalized() const noexcept {
        const auto m = magnitude();
        return Vector(dx() / m, dy() / m);
    }

    /// Returns the dot product of this `Vector` with another.
    ///
    /// @param other The other `Vector`.
    /// @return The dot product.
    constexpr float dot_product(const Vector &other) const noexcept {
        return dx() * other.dx() + dy() * other.dy();
    }

    /// Tests the `Vector` for approximate equivalency with another.
    ///
    /// @param other The other `Vector`.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    constexpr bool is_approximately(const Vector &other, float tolerance = Math::epsilon()) const noexcept {
        return Math::is_approximately(dx(), other.dx(), tolerance)
            && Math::is_approximately(dy(), other.dy(), tolerance);
    }

    template <typename std::size_t Index>
    constexpr const std::tuple_element_t<Index, Vector> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_dx;
        }
        if constexpr (Index == 1) {
            return m_dy;
        }
        std::unreachable();
    }

private:

    float m_dx;

    float m_dy;
};

namespace std {

    template <size_t Index>
    struct tuple_element<Index, Vector> : tuple_element<Index, tuple<float, float>> { };

    template <>
    struct tuple_size<Vector> {

        constexpr static size_t value = 2;
    };

    template <>
    struct hash<Vector> {

        size_t operator()(const Vector &vector) const noexcept {
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

        format_context::iterator format(const Vector &vector, format_context &context) const noexcept {
            const auto [dx, dy] = vector;
            return format_to(context.out(), "Vector(dx: {}, dy: {})", dx, dy);
        };
    };

    inline ostream &operator<<(ostream &stream, const Vector &vector) noexcept {
        return stream << format("{}", vector);
    }
}

constexpr Vector operator+(const Vector &vector, const Vector &other) noexcept {
    return Vector(vector.dx() + other.dx(), vector.dy() + other.dy());
}

constexpr Vector operator+(const Vector &vector, float magnitude) noexcept {
    return vector + Vector(magnitude, magnitude);
}

constexpr Vector operator+(float magnitude, const Vector &vector) noexcept {
    return vector + Vector(magnitude, magnitude);
}

constexpr Vector operator-(const Vector &vector) noexcept {
    return Vector(-vector.dx(), -vector.dy());
}

constexpr Vector operator-(const Vector &vector, const Vector &other) noexcept {
    return Vector(vector.dx() - other.dx(), vector.dy() - other.dy());
}

constexpr Vector operator-(const Vector &vector, float magnitude) noexcept {
    return vector - Vector(magnitude, magnitude);
}

constexpr Vector operator-(float magnitude, const Vector &vector) noexcept {
    return vector - Vector(magnitude, magnitude);
}

constexpr Vector operator*(const Vector &vector, const Vector &other) noexcept {
    return Vector(vector.dx() * other.dx(), vector.dy() * other.dy());
}

constexpr Vector operator*(const Vector &vector, float magnitude) noexcept {
    return vector * Vector(magnitude, magnitude);
}

constexpr Vector operator*(float magnitude, const Vector &vector) noexcept {
    return vector * Vector(magnitude, magnitude);
}

constexpr Vector operator/(const Vector &vector, const Vector &other) noexcept {
    return Vector(vector.dx() / other.dx(), vector.dy() / other.dy());
}

constexpr Vector operator/(const Vector &vector, float magnitude) noexcept {
    return vector / Vector(magnitude, magnitude);
}

constexpr Vector operator/(float magnitude, const Vector &vector) noexcept {
    return vector / Vector(magnitude, magnitude);
}

constexpr Vector &operator+=(Vector &vector, const Vector &other) noexcept {
    vector = vector + other;
    return vector;
}

constexpr Vector &operator+=(Vector &vector, float magnitude) noexcept {
    vector = vector + magnitude;
    return vector;
}

constexpr Vector &operator-=(Vector &vector, const Vector &other) noexcept {
    vector = vector - other;
    return vector;
}

constexpr Vector &operator-=(Vector &vector, float magnitude) noexcept {
    vector = vector - magnitude;
    return vector;
}

constexpr Vector &operator*=(Vector &vector, const Vector &other) noexcept {
    vector = vector * other;
    return vector;
}

constexpr Vector &operator*=(Vector &vector, float magnitude) noexcept {
    vector = vector * magnitude;
    return vector;
}

constexpr Vector &operator/=(Vector &vector, const Vector &other) noexcept {
    vector = vector / other;
    return vector;
}

constexpr Vector &operator/=(Vector &vector, float magnitude) noexcept {
    vector = vector / magnitude;
    return vector;
}
