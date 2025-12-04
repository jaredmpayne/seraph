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
