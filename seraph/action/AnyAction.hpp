#pragma once

#include <variant>

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
