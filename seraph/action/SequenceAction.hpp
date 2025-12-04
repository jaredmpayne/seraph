#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

class AnyAction;

class SequenceAction {

public:

    SequenceAction(const std::vector<AnyAction> &actions) noexcept;
    
    constexpr const std::vector<AnyAction> &actions() const noexcept {
        return m_actions;
    }

    float duration() const noexcept;

    AnyAction reversed() const noexcept;

private:

    std::vector<AnyAction> m_actions;
};
