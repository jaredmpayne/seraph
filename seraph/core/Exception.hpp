#pragma once

#include <compare>
#include <string>

class Exception {

public:

    constexpr Exception() noexcept = default;

    constexpr Exception(Exception &&) noexcept = default;

    constexpr Exception(const Exception &) noexcept = default;

    constexpr Exception &operator=(const Exception &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Exception &) const noexcept = default;

    constexpr Exception(const std::string &what) noexcept :
        m_what(what) { }

    constexpr const std::string &what() const noexcept {
        return m_what;
    }

private:

    std::string m_what;
};
