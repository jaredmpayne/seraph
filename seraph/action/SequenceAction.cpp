#include <seraph/action/SequenceAction.hpp>

#include <functional>
#include <ranges>
#include <vector>

#include <seraph/action/AnyAction.hpp>

SequenceAction::SequenceAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

float SequenceAction::duration() const noexcept {
    const auto &the_actions = actions();
    return std::transform_reduce(
        the_actions.cbegin(),
        the_actions.cend(),
        0.0f,
        std::plus(),
        [](const auto &action) { return action.duration(); }
    );
}

AnyAction SequenceAction::reversed() const noexcept {
    return SequenceAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::views::reverse
            | std::ranges::to<std::vector>()
    );
}
