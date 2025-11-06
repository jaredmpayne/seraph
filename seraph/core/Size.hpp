#pragma once

#include <compare>
#include <format>
#include <iostream>
#include <tuple>

#include <seraph/hash/SipHasher.hpp>

class Size {

public:

    constexpr Size() noexcept = default;

    constexpr Size(Size &&) noexcept = default;

    constexpr Size(const Size &) noexcept = default;

    constexpr Size &operator=(const Size &) = default;

    constexpr std::strong_ordering operator<=>(const Size &other) const noexcept = default;

    constexpr Size(float width, float height) noexcept :
        m_width(width),
        m_height(height) { }

    constexpr float width() const noexcept {
        return m_width;
    }

    inline void set_width(float width) noexcept {
        m_width = width;
    }

    constexpr float height() const noexcept {
        return m_height;
    }

    inline void set_height(float height) noexcept {
        m_height = height;
    }

    template<std::size_t Index>
    constexpr const std::tuple_element_t<Index, Size> &get() const noexcept {
        if constexpr (Index == 0) {
            return m_width;
        }
        if constexpr (Index == 1) {
            return m_height;
        }
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

        inline size_t operator()(const Size &size) const noexcept {
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

        inline format_context::iterator format(const Size &size, format_context &context) const noexcept {
            const auto [width, height] = size;
            return format_to(context.out(), "Size(width: {}, height: {})", width, height);
        };
    };

    inline ostream &operator<<(ostream &stream, const Size &size) noexcept {
        return stream << format("{}", size);
    }
}
