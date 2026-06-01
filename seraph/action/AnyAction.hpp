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

constexpr AnyAction FunctionAction::reversed() const noexcept {
    return *this;
}

constexpr AnyAction FunctionAction::erased() const noexcept {
    return *this;
}

constexpr InfiniteAction::InfiniteAction(const AnyAction &action) noexcept :
    m_action(action) { }

constexpr AnyAction InfiniteAction::reversed() const noexcept {
    return std::get<InfiniteAction>(action().reversed());
}

constexpr AnyAction InfiniteAction::erased() const noexcept {
    return *this;
}

constexpr AnyAction MoveAction::reversed() const noexcept {
    return MoveAction(delta().negative(), duration());
}

constexpr AnyAction MoveAction::erased() const noexcept {
    return *this;
}

constexpr ParallelAction::ParallelAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

constexpr float ParallelAction::duration() const noexcept {
    return std::ranges::max_element(actions(), std::less(), &AnyAction::duration)->duration();
}

constexpr AnyAction ParallelAction::reversed() const noexcept {
    return ParallelAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::ranges::to<std::vector>()
    );
}

constexpr AnyAction ParallelAction::erased() const noexcept {
    return *this;
}

constexpr RepeatAction::RepeatAction(const AnyAction &action, int count) noexcept :
    m_action(action),
    m_count(count) { }

constexpr float RepeatAction::duration() const noexcept {
    return action().duration() * count();
}

constexpr AnyAction RepeatAction::reversed() const noexcept {
    return RepeatAction(action().reversed(), count());
}

constexpr AnyAction RepeatAction::erased() const noexcept {
    return *this;
}

constexpr AnyAction RotateAction::reversed() const noexcept {
    return RotateAction(-1.0f * rotation(), duration());
}

constexpr AnyAction RotateAction::erased() const noexcept {
    return *this;
}

constexpr AnyAction ScaleAction::reversed() const noexcept {
    return ScaleAction(1.0f / delta(), duration());
}

constexpr AnyAction ScaleAction::erased() const noexcept {
    return *this;
}

constexpr SequenceAction::SequenceAction(const std::vector<AnyAction> &actions) noexcept :
    m_actions(actions) { }

constexpr float SequenceAction::duration() const noexcept {
    return std::transform_reduce(
        actions().cbegin(),
        actions().cend(),
        0.0f,
        std::plus(),
        [](const auto &action) { return action.duration(); }
    );
}

constexpr AnyAction SequenceAction::reversed() const noexcept {
    return SequenceAction(
        actions()
            | std::views::transform(&AnyAction::reversed)
            | std::views::reverse
            | std::ranges::to<std::vector>()
    );
}

constexpr AnyAction SequenceAction::erased() const noexcept {
    return *this;
}

constexpr AnyAction WaitAction::reversed() const noexcept {
    return *this;
}

constexpr AnyAction WaitAction::erased() const noexcept {
    return *this;
}
