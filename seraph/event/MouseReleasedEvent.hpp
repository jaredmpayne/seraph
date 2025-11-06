#pragma once

#include <seraph/core/MouseCode.hpp>
#include <seraph/core/Point.hpp>

class MouseReleasedEvent {

public:

    constexpr MouseReleasedEvent(MouseCode mouse_code, const Point &position) noexcept :
        m_mouse_code(mouse_code),
        m_position(position) { }

    constexpr MouseCode mouse_code() const noexcept {
        return m_mouse_code;
    }

    constexpr const Point &position() const noexcept {
        return m_position;
    }

private:

    MouseCode m_mouse_code;

    Point m_position;
};
