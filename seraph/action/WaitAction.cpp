#include <seraph/action/WaitAction.hpp>

#include <seraph/action/AnyAction.hpp>

AnyAction WaitAction::reversed() const noexcept {
    return *this;
}
