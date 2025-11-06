#pragma once

#include <chrono>

/// The class that keeps time for the main game loop.
class Clock {

public:

    /// Constructs a `Clock` that takes note of the current time.
    constexpr Clock() noexcept = default;

    constexpr Clock(Clock &&) noexcept = default;

    constexpr Clock(const Clock &) noexcept = default;

    constexpr Clock &operator=(const Clock &) noexcept = default;

    constexpr std::strong_ordering operator<=>(const Clock &) const noexcept = default;

    /// The time passed since the `Clock` was either constructed or last restarted.
    constexpr float time_elapsed() const noexcept {
        return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_previous).count();
    }

    /// Resets the `Clock` and returns the prior time elapsed.
    inline float restart() noexcept {
        const auto previous = m_previous;
        m_previous = std::chrono::steady_clock::now();
        return std::chrono::duration<float>(m_previous - previous).count();
    }

private:

    std::chrono::steady_clock::time_point m_previous = std::chrono::steady_clock::now();
};
