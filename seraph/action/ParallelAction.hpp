#pragma once

#include <vector>

class AnyAction;

class ParallelAction {

public:

    // NOTE: Defined in AnyAction.hpp
    constexpr ParallelAction(const std::vector<AnyAction> &actions) noexcept;

    constexpr const std::vector<AnyAction> &actions() const noexcept {
        return m_actions;
    }

    // NOTE: Defined in AnyAction.hpp
    constexpr float duration() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction reversed() const noexcept;

    // NOTE: Defined in AnyAction.hpp
    constexpr AnyAction erased() const noexcept;

private:

    std::vector<AnyAction> m_actions;
};
