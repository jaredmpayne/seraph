#pragma once

#include <memory>

/// A container for storing copyable objects on the heap.
template <typename T>
class Box {

public:

    constexpr Box(const Box<T> &other) noexcept :
        Box(other.value()) { }

    constexpr Box(const T &value) noexcept :
        m_value(std::make_unique<T>(value)) { }

    constexpr const T &value() const noexcept {
        return *m_value;
    }

private:

    std::unique_ptr<T> m_value;
};
