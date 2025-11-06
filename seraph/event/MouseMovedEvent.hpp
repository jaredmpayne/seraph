#pragma once

#include <seraph/core/Point.hpp>

class MouseMovedEvent {

public:

    constexpr MouseMovedEvent(const Point &position) noexcept :
        m_position(position) { }

    constexpr const Point &position() const noexcept {
        return m_position;
    }

private:

    Point m_position;
};
