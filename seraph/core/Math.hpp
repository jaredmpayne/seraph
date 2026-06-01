#pragma once

#include <cmath>

class Math {

public:

    /// A very small floating-point value.
    ///
    /// Useful as a tolerance for testing if two floating-point values are
    /// approximately equal in most use cases.
    static constexpr float epsilon() noexcept {
        return 1.0e-6f;
    }

    /// Tests if two floating-point values are approximately equal.
    ///
    /// @param x, y The two values.
    /// @param tolerance The smallest tolerable difference between values.
    /// @return `true` if the values are equal within `tolerance`, otherwise `false`.
    static constexpr bool is_approximately(float x, float y, float tolerance = epsilon()) noexcept {
        return std::abs(x - y) <= tolerance;
    }

    /// Tests if a given value is inside an inclusive range.
    ///
    /// @param value The tested value.
    /// @param min The range minimum.
    /// @param max The range maximum.
    template <typename T>
    static constexpr bool is_in_range(const T &value, const T &min, const T &max) noexcept {
        return value >= min && value <= max;
    }
};
