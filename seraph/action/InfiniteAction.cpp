#include <seraph/action/InfiniteAction.hpp>

#include <seraph/action/AnyAction.hpp>

InfiniteAction::InfiniteAction(const AnyAction &action) noexcept :
    m_action(action) { }

AnyAction InfiniteAction::reversed() const noexcept {
    return action().reversed();
}
