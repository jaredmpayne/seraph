#include <seraph/action/ScaleAction.hpp>

#include <seraph/action/AnyAction.hpp>

AnyAction ScaleAction::reversed() const noexcept {
    return ScaleAction(1.0f / delta(), duration());
}
