#pragma once

#include <seraph/core/Box.hpp>

class AnyAction;

class RepeatAction {

public:

    RepeatAction(const AnyAction &action, int count) noexcept;

    constexpr const AnyAction &action() const noexcept {
        return m_action.value();
    }

    constexpr int count() const noexcept {
        return m_count;
    }

    float duration() const noexcept;

    AnyAction reversed() const noexcept;

private:

    Box<AnyAction> m_action;

    int m_count;
};
