#pragma once

class AnyAction;

class WaitAction {

public:

    constexpr WaitAction(float duration) noexcept :
        m_duration(duration) { }

    constexpr float duration() const noexcept {
        return m_duration;
    }

    AnyAction reversed() const noexcept;

private:

    float m_duration;
};
