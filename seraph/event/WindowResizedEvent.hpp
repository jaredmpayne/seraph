#pragma once

#include <seraph/core/Size.hpp>

class AnyEvent;

class WindowResizedEvent {

public:

    constexpr WindowResizedEvent(const Size &size) noexcept :
        m_size(size) { }

    constexpr const Size &size() const noexcept {
        return m_size;
    }

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;

private:

    Size m_size;
};
