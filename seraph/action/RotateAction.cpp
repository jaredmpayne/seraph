#include <seraph/action/RotateAction.hpp>

#include <seraph/action/AnyAction.hpp>

AnyAction RotateAction::reversed() const noexcept {
    return RotateAction(-1.0f * rotation(), duration());
}
