#pragma once

#include <memory>

/// A container for storing copyable objects on the heap.
///
/// This object is effectively a wrapper around an `std::unique_ptr` that
/// creates a new copy of the underlying object with its own `std::unique_ptr`
/// when copied. When a `Box` is destroyed, its underlying `std::unique_ptr`
/// and its owned object are destroyed as well.
template <typename T>
class Box {

public:

    /// Constructs a `Box` containing the given value.
    constexpr Box(const T &value) noexcept :
        m_value(std::make_unique<T>(value)) { }

    /// Moves a `Box` from another.
    constexpr Box(Box<T> &&) noexcept = default;

    /// Copies a `Box` from another.
    constexpr Box(const Box<T> &other) noexcept :
        Box(other.value()) { }

    /// Move assigns a `Box` from another.
    constexpr Box<T> &operator=(Box<T> &&) noexcept = default;

    /// Copy assigns a `Box` from another.
    constexpr Box<T> &&operator=(const Box<T> &other) noexcept {
        return Box<T>(other.value());
    }

    /// The contained value.
    constexpr const T &value() const noexcept {
        return *m_value;
    }

private:

    std::unique_ptr<T> m_value;
};
