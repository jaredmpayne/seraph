#pragma once

#include <algorithm>
#include <functional>
#include <numeric>
#include <ranges>
#include <variant>
#include <vector>

#include <seraph/action/FunctionAction.hpp>
#include <seraph/action/InfiniteAction.hpp>
#include <seraph/action/MoveAction.hpp>
#include <seraph/action/ParallelAction.hpp>
#include <seraph/action/RepeatAction.hpp>
#include <seraph/action/RotateAction.hpp>
#include <seraph/action/ScaleAction.hpp>
#include <seraph/action/SequenceAction.hpp>
#include <seraph/action/WaitAction.hpp>

namespace detail {

using AnyActionVariant = std::variant<
    FunctionAction,
    InfiniteAction,
    MoveAction,
    ParallelAction,
    RepeatAction,
    RotateAction,
    ScaleAction,
    SequenceAction,
    WaitAction
>;

}

class AnyAction : public detail::AnyActionVariant {

public:

    using detail::AnyActionVariant::variant;

    constexpr float duration() const noexcept {
        return std::visit([](const auto &action) { return action.duration(); }, *this);
    }

    constexpr AnyAction reversed() const noexcept {
        return std::visit([](const auto &action) { return action.reversed(); }, *this);
    }
};

inline AnyAction FunctionAction::reversed() const noexcept {
    return *this;
}

inline InfiniteAction::InfiniteAction(const AnyAction &action) noexcept :
    m_action(action) { }

inline AnyAction InfiniteAction::reversed() const noexcept {
    return action().reversed();
}

inline AnyAction MoveAction::reversed() const noexcept {
    return MoveAction(delta().reversed(), duration());
}

inline ParallelAction::ParallelAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

inline float ParallelAction::duration() const noexcept {
    return std::ranges::max_element(actions(), std::less(), &AnyAction::duration)->duration();
}

inline AnyAction ParallelAction::reversed() const noexcept {
    return ParallelAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::ranges::to<std::vector>()
    );
}

inline RepeatAction::RepeatAction(const AnyAction &action, int count) noexcept :
    m_action(action),
    m_count(count) { }

inline float RepeatAction::duration() const noexcept {
    return action().duration() * count();
}

inline AnyAction RepeatAction::reversed() const noexcept {
    return RepeatAction(action().reversed(), count());
}

inline AnyAction RotateAction::reversed() const noexcept {
    return RotateAction(-1.0f * rotation(), duration());
}

inline AnyAction ScaleAction::reversed() const noexcept {
    return ScaleAction(1.0f / delta(), duration());
}

inline SequenceAction::SequenceAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

inline float SequenceAction::duration() const noexcept {
    return std::transform_reduce(
        actions().cbegin(),
        actions().cend(),
        0.0f,
        std::plus(),
        [](const auto &action) { return action.duration(); }
    );
}

inline AnyAction SequenceAction::reversed() const noexcept {
    return SequenceAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::views::reverse
            | std::ranges::to<std::vector>()
    );
}

inline AnyAction WaitAction::reversed() const noexcept {
    return *this;
}
