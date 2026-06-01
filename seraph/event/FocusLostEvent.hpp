#pragma once

class AnyEvent;

class FocusLostEvent {

public:

    constexpr FocusLostEvent() noexcept = default;

    // NOTE: Defined in AnyEvent.hpp
    constexpr AnyEvent erased() const noexcept;
};
