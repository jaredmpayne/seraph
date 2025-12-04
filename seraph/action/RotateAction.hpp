#pragma once

class AnyAction;

class RotateAction {

public:

    constexpr RotateAction(float rotation, float duration) noexcept :
        m_rotation(rotation),
        m_duration(duration) { }
    
    constexpr float rotation() const noexcept {
        return m_rotation;
    }

    constexpr float duration() const noexcept {
        return m_duration;
    }

    AnyAction reversed() const noexcept;

private:

    float m_rotation;

    float m_duration;
};
