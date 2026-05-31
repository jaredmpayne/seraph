#pragma once

#include <vector>

class AnyAction;

class ParallelAction {

public:

    // NOTE: Defined in AnyAction.hpp
    ParallelAction(const std::vector<AnyAction> &actions) noexcept;

    constexpr const std::vector<AnyAction> &actions() const noexcept {
        return m_actions;
    }

    // NOTE: Defined in AnyAction.hpp
    float duration() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    AnyAction reversed() const noexcept;

private:

    std::vector<AnyAction> m_actions;
};
