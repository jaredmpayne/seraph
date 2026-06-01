#pragma once

class AnyEvent;

class FocusGainedEvent {

public:

    constexpr FocusGainedEvent() noexcept = default;

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;
};
