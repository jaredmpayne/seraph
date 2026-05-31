#pragma once

#include <unordered_set>

#include <seraph/core/KeyCode.hpp>
#include <seraph/core/MouseCode.hpp>
#include <seraph/core/Point.hpp>

/// Tracks user inputs from keyboard, mouse, and other sources.
class Input {

public:

    /// Returns a boolean indicating if any key is pressed or held this frame.
    constexpr bool any_key() noexcept {
        return !m_key.empty();
    }

    /// Returns a boolean indicating if any key is pressed this frame.
    constexpr bool any_key_down() noexcept {
        return !m_key_down.empty();
    }

    /// Returns a boolean indicating if the given key is pressed or held this frame.
    constexpr bool key(KeyCode key_code) noexcept {
        return m_key.contains(key_code);
    }

    /// Returns a boolean indicating if the given key is released this frame.
    constexpr bool key_up(KeyCode key_code) noexcept {
        return m_key_up.contains(key_code);
    }

    /// Returns a boolean indicating if the given key is pressed this frame.
    constexpr bool key_down(KeyCode key_code) noexcept {
        return m_key_down.contains(key_code);
    }

    /// Returns a boolean indicating if the given mouse button is pressed or
    /// held this frame.
    constexpr bool mouse(MouseCode mouse_code) noexcept {
        return m_mouse.contains(mouse_code);
    }

    /// Returns a boolean indicating if the given mouse button is released
    /// this frame.
    constexpr bool mouse_up(MouseCode mouse_code) noexcept {
        return m_mouse_up.contains(mouse_code);
    }

    /// Returns a boolean indicating if the given mouse button is pressed this frame.
    constexpr bool mouse_down(MouseCode mouse_code) noexcept {
        return m_mouse_down.contains(mouse_code);
    }

    /// Returns the mouse cursor's position.
    constexpr const Point &mouse_position() noexcept {
        return m_mouse_position;
    }

private:
friend class EventSystem;

    // To be called at the start of each game frame.
    void update() noexcept {
        m_key_up.clear();
        m_key_down.clear();
    }

    void set_key_up(KeyCode key_code) noexcept {
        m_key_up.insert(key_code);
        m_key.erase(key_code);
    }

    void set_key_down(KeyCode key_code) noexcept {
        m_key_down.insert(key_code);
        m_key.insert(key_code);
    }

    void set_mouse_up(MouseCode mouse_code) noexcept {
        m_mouse_up.insert(mouse_code);
        m_mouse.erase(mouse_code);
    }

    void set_mouse_down(MouseCode mouse_code) noexcept {
        m_mouse_down.insert(mouse_code);
        m_mouse.insert(mouse_code);
    }

    void set_mouse_position(const Point &mouse_position) noexcept {
        m_mouse_position = mouse_position;
    }

private:

    std::unordered_set<KeyCode> m_key;

    std::unordered_set<KeyCode> m_key_up;

    std::unordered_set<KeyCode> m_key_down;

    std::unordered_set<MouseCode> m_mouse;

    std::unordered_set<MouseCode> m_mouse_up;

    std::unordered_set<MouseCode> m_mouse_down;

    Point m_mouse_position;
};
