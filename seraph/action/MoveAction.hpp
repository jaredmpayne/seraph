#pragma once

#include <seraph/core/Vector.hpp>

class AnyAction;

class MoveAction {

public:

    constexpr MoveAction(float dx, float dy, float duration) noexcept :
        MoveAction(Vector(dx, dy), duration) { }

    constexpr MoveAction(const Vector &delta, float duration) noexcept :
        m_delta(delta),
        m_duration(duration) { }

    constexpr const Vector &delta() const noexcept {
        return m_delta;
    }

    constexpr float duration() const noexcept {
        return m_duration;
    }

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction reversed() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction erased() const noexcept;

private:

    Vector m_delta;

    float m_duration;
};
