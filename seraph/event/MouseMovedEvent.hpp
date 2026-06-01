#pragma once

#include <seraph/core/Point.hpp>

class AnyEvent;

class MouseMovedEvent {

public:

    constexpr MouseMovedEvent(const Point &position) noexcept :
        m_position(position) { }

    constexpr const Point &position() const noexcept {
        return m_position;
    }

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;

private:

    Point m_position;
};
