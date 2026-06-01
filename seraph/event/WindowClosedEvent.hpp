#pragma once

class AnyEvent;

class WindowClosedEvent {

public:

    constexpr WindowClosedEvent() noexcept = default;

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;
};
