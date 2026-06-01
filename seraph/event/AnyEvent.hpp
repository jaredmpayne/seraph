#pragma once

#include <variant>

#include <seraph/event/FocusGainedEvent.hpp>
#include <seraph/event/FocusLostEvent.hpp>
#include <seraph/event/KeyPressedEvent.hpp>
#include <seraph/event/KeyReleasedEvent.hpp>
#include <seraph/event/MouseMovedEvent.hpp>
#include <seraph/event/MousePressedEvent.hpp>
#include <seraph/event/MouseReleasedEvent.hpp>
#include <seraph/event/WindowClosedEvent.hpp>
#include <seraph/event/WindowResizedEvent.hpp>

namespace detail {

using AnyEventVariant = std::variant<
    FocusGainedEvent,
    FocusLostEvent,
    KeyPressedEvent,
    KeyReleasedEvent,
    MouseMovedEvent,
    MousePressedEvent,
    MouseReleasedEvent,
    WindowClosedEvent,
    WindowResizedEvent
>;

}

class AnyEvent : public detail::AnyEventVariant {

public:

    using detail::AnyEventVariant::variant;
};

inline constexpr AnyEvent FocusGainedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent FocusLostEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent KeyPressedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent KeyReleasedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent MouseMovedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent MousePressedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent MouseReleasedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent WindowClosedEvent::erased() const noexcept {
    return *this;
}

inline constexpr AnyEvent WindowResizedEvent::erased() const noexcept {
    return *this;
}
