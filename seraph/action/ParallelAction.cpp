#include <seraph/action/ParallelAction.hpp>

#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include <seraph/action/AnyAction.hpp>

ParallelAction::ParallelAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

float ParallelAction::duration() const noexcept {
    return std::ranges::max_element(actions(), std::less(), &AnyAction::duration)->duration();
}

AnyAction ParallelAction::reversed() const noexcept {
    return ParallelAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::ranges::to<std::vector>()
    );
}
