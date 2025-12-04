#include <seraph/action/RepeatAction.hpp>

#include <seraph/action/AnyAction.hpp>

RepeatAction::RepeatAction(const AnyAction &action, int count) noexcept :
    m_action(action),
    m_count(count) { }

float RepeatAction::duration() const noexcept {
    return action().duration() * count();
}

AnyAction RepeatAction::reversed() const noexcept {
    return RepeatAction(action().reversed(), count());
}
