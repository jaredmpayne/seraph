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

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction reversed() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction erased() const noexcept;

private:

    float m_rotation;

    float m_duration;
};
