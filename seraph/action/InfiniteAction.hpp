#pragma once

#include <numeric>

#include <seraph/core/Box.hpp>

class AnyAction;

class InfiniteAction {

public:

    InfiniteAction(const AnyAction &action) noexcept;

    constexpr const AnyAction &action() const noexcept {
        return m_action.value();
    }

    constexpr float duration() const noexcept {
        return std::numeric_limits<float>::infinity();
    }

    AnyAction reversed() const noexcept;

private:

    Box<AnyAction> m_action;
};
