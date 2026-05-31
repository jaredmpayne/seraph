#pragma once

#include <chrono>

/// A class that tracks the time since its object was constructed or last
/// restarted.
///
/// This class was originally created to keep track of time for the main engine loop.
/// It has been kept in the public library as a useful timekeeping tool.
class Clock {

public:

    /// Constructs a `Clock` that takes note of the current time.
    constexpr Clock() noexcept = default;

    /// Moves a `Clock` from another.
    constexpr Clock(Clock &&) noexcept = default;

    /// Copies a `Clock` from another.
    constexpr Clock(const Clock &) noexcept = default;

    /// Move assigns a `Clock` from another.
    constexpr Clock &operator=(Clock &&) noexcept = default;

    /// Copy assigns a `Clock` from another.
    constexpr Clock &operator=(const Clock &) noexcept = default;

    /// Compares two `Point` objects.
    ///
    /// The objects are effectively compared based on their last recorded time.
    constexpr auto operator<=>(const Clock &) const noexcept = default;

    /// The time passed since the `Clock` was either constructed or last
    /// restarted.
    ///
    /// Effectively, the current time minus the previously recorded time.
    constexpr float time_elapsed() const noexcept {
        return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_previous).count();
    }

    /// Resets the `Clock` and returns the prior time elapsed.
    float restart() noexcept {
        const auto previous = m_previous;
        m_previous = std::chrono::steady_clock::now();
        return std::chrono::duration<float>(m_previous - previous).count();
    }

private:

    std::chrono::steady_clock::time_point m_previous = std::chrono::steady_clock::now();
};
