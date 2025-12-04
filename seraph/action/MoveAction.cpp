#include <seraph/action/MoveAction.hpp>

#include <seraph/action/AnyAction.hpp>

AnyAction MoveAction::reversed() const noexcept {
    return MoveAction(delta().reversed(), duration());
}
