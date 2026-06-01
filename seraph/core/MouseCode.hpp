#pragma once

#include <cstddef>
#include <optional>

#include <seraph/core/Math.hpp>

class MouseCode {

public:

    static constexpr bool is_in_range(int value) noexcept {
        return Math::is_in_range(value, *left(), *middle());
    }

    static std::optional<MouseCode> from_value(int value) noexcept {
        if (is_in_range(value)) {
            return MouseCode(value);
        }
        return std::nullopt;
    }

    static constexpr MouseCode left() noexcept {
        return MouseCode(0);
    }

    static constexpr MouseCode right() noexcept {
        return MouseCode(1);
    }

    static constexpr MouseCode middle() noexcept {
        return MouseCode(2);
    }

    constexpr auto operator<=>(const MouseCode &) const noexcept = default;

    constexpr int operator*() const noexcept {
        return value();
    }

    constexpr int value() const noexcept {
        return m_value;
    }

private:

    constexpr MouseCode(int value) noexcept :
        m_value(value) { }

    int m_value;
};

namespace std {

    template <>
    struct hash<MouseCode> {

        size_t operator()(const MouseCode &code) const noexcept {
            return *code;
        }
    };
}
