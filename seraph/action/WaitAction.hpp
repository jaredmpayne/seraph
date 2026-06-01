#pragma once

class AnyAction;

class WaitAction {

public:

    constexpr WaitAction(float duration) noexcept :
        m_duration(duration) { }

    constexpr float duration() const noexcept {
        return m_duration;
    }

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction reversed() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction erased() const noexcept;

private:

    float m_duration;
};
