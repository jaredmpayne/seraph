#pragma once

#include <unordered_set>

#include <seraph/core/KeyCode.hpp>
#include <seraph/core/MouseCode.hpp>
#include <seraph/core/Point.hpp>

class Game;

/// Tracks user inputs from keyboard, mouse, and other sources.
class Input {

public:

    /// The program's shared `Input` object. Creating another is not typically necesary.
    constexpr static Input &shared() noexcept {
        static auto instance = Input();
        return instance;
    }

    constexpr bool any_key() const noexcept {
        return !m_key.empty();
    }

    constexpr bool any_key_down() const noexcept {
        return !m_key_down.empty();
    }

    /// Returns a boolean indicating if the given key was pressed or held down this frame.
    constexpr bool key(KeyCode key_code) const noexcept {
        return m_key.contains(key_code);
    }

    /// Returns a boolean indicating if the given key was released up this frame.
    constexpr bool key_up(KeyCode key_code) const noexcept {
        return m_key_up.contains(key_code);
    }

    /// Returns a boolean indicating if the given key was pressed down this frame.
    constexpr bool key_down(KeyCode key_code) const noexcept {
        return m_key_down.contains(key_code);
    }

    constexpr bool mouse(MouseCode mouse_code) const noexcept {
        return m_mouse.contains(mouse_code);
    }

    constexpr bool mouse_up(MouseCode mouse_code) const noexcept {
        return m_mouse_up.contains(mouse_code);
    }

    constexpr bool mouse_down(MouseCode mouse_code) const noexcept {
        return m_mouse_down.contains(mouse_code);
    }

    constexpr const Point &mouse_position() const noexcept {
        return m_mouse_position;
    } 

private:
friend class Game;

    inline void set_key_up(KeyCode key_code) noexcept {
        m_key_up.insert(key_code);
        m_key.erase(key_code);
    }

    inline void set_key_down(KeyCode key_code) noexcept {
        m_key_down.insert(key_code);
        m_key.insert(key_code);
    }

    inline void set_mouse_up(MouseCode mouse_code) noexcept {
        m_mouse_up.insert(mouse_code);
        m_mouse.erase(mouse_code);
    }

    inline void set_mouse_down(MouseCode mouse_code) noexcept {
        m_mouse_down.insert(mouse_code);
        m_mouse.insert(mouse_code);
    }

    inline void set_mouse_position(const Point &mouse_position) noexcept {
        m_mouse_position = mouse_position;
    }

private:

    Input() noexcept = default;

    inline void tick_next_update() noexcept {
        m_key_up.clear();
        m_key_down.clear();
    }

    std::unordered_set<KeyCode> m_key;

    std::unordered_set<KeyCode> m_key_up;

    std::unordered_set<KeyCode> m_key_down;

    std::unordered_set<MouseCode> m_mouse;

    std::unordered_set<MouseCode> m_mouse_up;

    std::unordered_set<MouseCode> m_mouse_down;

    Point m_mouse_position;
};
