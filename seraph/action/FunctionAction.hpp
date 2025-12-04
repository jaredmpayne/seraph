#pragma once

#include <functional>

class AnyAction;

class FunctionAction {

public:

    FunctionAction(const std::function<void()> &function) noexcept :
        m_function(function) { }

    constexpr const std::function<void()> &function() const noexcept {
        return m_function;
    }

    constexpr float duration() const noexcept {
        return 0.0f;
    }

    AnyAction reversed() const noexcept;

private:

    std::function<void()> m_function;
};
