#pragma once

#include <string>

/// An object to be thrown when the library encounters an error that cannot be
/// adequately represented by a certain return value.
///
/// Effectively a wrapper for a `std::string` containing an error message.
class Exception {

public:

    /// Constructs an `Exception` with an empty error message.
    constexpr Exception() noexcept = default;

    /// Constructs an `Exception` with the given error message.
    ///
    /// @param what The error message.
    constexpr Exception(const std::string &what) noexcept :
        m_what(what) { }

    /// Moves an `Exception` from another.
    constexpr Exception(Exception &&) noexcept = default;

    /// Copies an `Exception` from another.
    constexpr Exception(const Exception &) noexcept = default;

    /// Move assigns an `Exception` from another.
    constexpr Exception &operator=(Exception &&) noexcept = default;

    /// Copy assigns an `Exception` from another.
    constexpr Exception &operator=(const Exception &) noexcept = default;

    /// Compares two `Exception` objects.
    ///
    /// The objects are effectively compared as tuples `(what())`.
    constexpr auto operator<=>(const Exception &) const noexcept = default;

    /// The `Exception`'s error message.
    constexpr const std::string &what() const noexcept {
        return m_what;
    }

private:

    std::string m_what;
};
