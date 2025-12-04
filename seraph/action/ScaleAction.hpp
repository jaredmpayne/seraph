#pragma once

#include <seraph/core/Vector.hpp>

class AnyAction;

class ScaleAction {

public:

    constexpr ScaleAction(const Vector &delta, float duration) noexcept :
        m_delta(delta),
        m_duration(duration) { }

    constexpr const Vector &delta() const noexcept {
        return m_delta;
    }

    constexpr float duration() const noexcept {
        return m_duration;
    }

    AnyAction reversed() const noexcept;

private:

    Vector m_delta;

    float m_duration;
};
