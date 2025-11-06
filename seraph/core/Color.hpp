#pragma once

#include <compare>
#include <cstdint>
#include <format>
#include <iostream>
#include <tuple>

#include <seraph/hash/SipHasher.hpp>

class Color {

public:

    /// Constructs the default `Color` of black.
    ///
    /// Effectively equal to `Color::black()` which is `Color(0, 0, 0, 255)`.
    constexpr Color() noexcept = default;

    constexpr Color(Color &&) noexcept = default;

    constexpr Color(const Color &) noexcept = default;

    constexpr Color &operator=(const Color &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Color &other) const noexcept = default;

    /// Constructs a `Color` of the given hue and alpha values.
    constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255) noexcept :
        m_r(r),
        m_g(g),
        m_b(b),
        m_a(a) { }

    /// The color black, or `Color(0, 0, 0, 255)`.
    static constexpr Color black() noexcept {
        return Color(0, 0, 0);
    }

    /// The color red, or `Color(255, 0, 0, 255)`.
    static constexpr Color red() noexcept {
        return Color(255, 0, 0);
    }

    /// The color green, or `Color(0, 255, 0, 255)`.
    static constexpr Color green() noexcept {
        return Color(0, 255, 0);
    }

    /// The color blue, or `Color(0, 0, 255, 255)`.
    static constexpr Color blue() noexcept {
        return Color(0, 0, 255);
    }

    /// The color yellow, or `Color(255, 255, 0, 255)`.
    static constexpr Color yellow() noexcept {
        return Color(255, 255, 0);
    }

    /// The color cyan, or `Color(0, 255, 255, 255)`.
    static constexpr Color cyan() noexcept {
        return Color(0, 255, 255);
    }

    /// The color magenta, or `Color(255, 255, 0, 255)`.
    static constexpr Color magenta() noexcept {
        return Color(255, 0, 255);
    }

    /// The color white, or `Color(255, 255, 255, 255)`.
    static constexpr Color white() noexcept {
        return Color(255, 255, 255);
    }

    /// A transparent shade, specifically black set to transparent, or `Color(0, 0, 0, 255)`.
    static constexpr Color transparent() noexcept {
        return Color(0, 0, 0, 0);
    }

    /// Returns the red component of the `Color`.
    constexpr std::uint8_t r() const noexcept {
        return m_r;
    }

    inline void set_r(std::uint8_t r) noexcept {
        m_r = r;
    }

    /// Returns the green component of the `Color`.
    constexpr std::uint8_t g() const noexcept {
        return m_g;
    }

    inline void set_g(std::uint8_t g) noexcept {
        m_g = g;
    }

    /// Returns the blue component of the `Color`.
    constexpr std::uint8_t b() const noexcept {
        return m_b;
    }

    inline void set_b(std::uint8_t b) noexcept {
        m_b = b;
    }

    /// Returns the alpha component of the `Color`.
    constexpr std::uint8_t a() const noexcept {
        return m_a;
    }

    inline void set_a(std::uint8_t a) noexcept {
        m_a = a;
    }

    template <typename std::size_t Index>
    constexpr std::tuple_element_t<Index, Color> get() const noexcept {
        if constexpr (Index == 0) {
            return r();
        }
        if constexpr (Index == 1) {
            return g();
        }
        if constexpr (Index == 2) {
            return b();
        }
        if constexpr (Index == 3) {
            return a();
        }
    }

private:

    std::uint8_t m_r;

    std::uint8_t m_g;

    std::uint8_t m_b;

    std::uint8_t m_a = 255;
};

namespace std {

    template <>
    struct tuple_size<Color> {

        constexpr static size_t value = 4;
    };

    template <size_t Index>
    struct tuple_element<Index, Color> : tuple_element<Index, tuple<uint8_t, uint8_t, uint8_t, uint8_t>> { };

    template <>
    struct hash<Color> {

        inline size_t operator()(const Color &color) const noexcept {
            auto hasher = SipHasher();
            hasher.write(color);
            return hasher.value();
        }
    };

    template <>
    struct formatter<Color> {

        constexpr const char *parse(format_parse_context &context) const noexcept {
            return context.begin();
        }

        inline format_context::iterator format(const Color &color, format_context &context) const noexcept {
            const auto [r, g, b, a] = color;
            return format_to(context.out(), "Color(r: {}, g: {}, b: {}, a: {})", r, g, b, a);
        };
    };

    inline ostream &operator<<(ostream &stream, const Color &color) noexcept {
        return stream << format("{}", color);
    }
}
