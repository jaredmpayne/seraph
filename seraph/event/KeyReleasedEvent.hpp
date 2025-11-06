#pragma once

#include <seraph/core/KeyCode.hpp>

class KeyReleasedEvent {

public:

    constexpr KeyReleasedEvent(
        KeyCode key_code,
        bool is_ctrl_down = false,
        bool is_alt_down = false,
        bool is_shift_down = false,
        bool is_super_down = false
    ) noexcept :
        m_key_code(key_code),
        m_is_ctrl_down(is_ctrl_down),
        m_is_alt_down(is_alt_down),
        m_is_shift_down(is_shift_down),
        m_is_super_down(is_super_down) { }

    constexpr KeyCode key_code() const noexcept {
        return m_key_code;
    }

    constexpr bool is_ctrl_down() const noexcept {
        return m_is_ctrl_down;
    }

    constexpr bool is_alt_down() const noexcept {
        return m_is_alt_down;
    }

    constexpr bool is_shift_down() const noexcept {
        return m_is_shift_down;
    }

    constexpr bool is_super_down() const noexcept {
        return m_is_super_down;
    }

private:

    KeyCode m_key_code;

    bool m_is_ctrl_down;

    bool m_is_alt_down;

    bool m_is_shift_down;

    bool m_is_super_down;
};
