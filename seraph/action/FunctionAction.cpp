#include <seraph/action/FunctionAction.hpp>

#include <seraph/action/AnyAction.hpp>

AnyAction FunctionAction::reversed() const noexcept {
    return *this;
}
