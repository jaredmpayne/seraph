#pragma once

#include <seraph/core/Box.hpp>

class AnyAction;

class RepeatAction {

public:

    // NOTE: Defined in AnyAction.hpp
    constexpr RepeatAction(const AnyAction &action, int count) noexcept;

    constexpr const AnyAction &action() const noexcept {
        return m_action.value();
    }

    constexpr int count() const noexcept {
        return m_count;
    }

    constexpr float duration() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction reversed() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction erased() const noexcept;

private:

    Box<AnyAction> m_action;

    int m_count;
};
