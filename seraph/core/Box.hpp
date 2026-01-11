#pragma once

#include <memory>

/// A container for storing copyable objects on the heap.
///
/// This object is effectively a wrapper around an `std::unique_ptr` that
/// creates a new copy of the underlying object with its own `std::unique_ptr`
/// when copied.
template <typename T>
class Box {

public:

    constexpr Box(const T &value) noexcept :
        m_value(std::make_unique<T>(value)) { }

    constexpr Box(const Box<T> &other) noexcept :
        Box(other.value()) { }

    constexpr const T &value() const noexcept {
        return *m_value;
    }

private:

    std::unique_ptr<T> m_value;
};
