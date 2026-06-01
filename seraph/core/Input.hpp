#pragma once

#include <unordered_set>

#include <seraph/core/KeyCode.hpp>
#include <seraph/core/MouseCode.hpp>
#include <seraph/core/ScanCode.hpp>
#include <seraph/core/Point.hpp>

/// Tracks user inputs from keyboard, mouse, and other sources.
class Input {

public:

    /// Returns a boolean indicating if any key has been pressed or held this frame.
    constexpr bool any_key() const noexcept {
        return !m_key.empty();
    }

    /// Returns a boolean indicating if any key has been pressed this frame.
    constexpr bool any_key_down() const noexcept {
        return !m_key_down.empty();
    }

    /// Returns a boolean indicating if the given key has been pressed or held this frame.
    constexpr bool key(ScanCode code) const noexcept {
        return m_key.contains(code);
    }

    /// Returns a boolean indicating if the localized key has been pressed or
    /// held this frame.
    constexpr bool key(KeyCode code) const noexcept {
        return key(*code.delocalized());
    }

    /// Returns a boolean indicating if the given key has been released this frame.
    constexpr bool key_up(ScanCode code) const noexcept {
        return m_key_up.contains(code);
    }

    /// Returns a boolean indicating if the localized key has been released this frame.
    constexpr bool key_up(KeyCode code) const noexcept {
        return key_up(*code.delocalized());
    }

    /// Returns a boolean indicating if the given key has been pressed this frame.
    constexpr bool key_down(ScanCode code) const noexcept {
        return m_key_down.contains(code);
    }

    /// Returns a boolean indicating if the localized key has been pressed this frame.
    constexpr bool key_down(KeyCode code) const noexcept {
        return key_down(*code.delocalized());
    }

    /// Returns a boolean indicating if the given mouse button has been pressed or
    /// held this frame.
    constexpr bool mouse(MouseCode code) const noexcept {
        return m_mouse.contains(code);
    }

    /// Returns a boolean indicating if the given mouse button has been released
    /// this frame.
    constexpr bool mouse_up(MouseCode code) const noexcept {
        return m_mouse_up.contains(code);
    }

    /// Returns a boolean indicating if the given mouse button has been pressed this frame.
    constexpr bool mouse_down(MouseCode code) const noexcept {
        return m_mouse_down.contains(code);
    }

    /// Returns the mouse cursor's position.
    constexpr const Point &mouse_position() const noexcept {
        return m_mouse_position;
    }

private:
friend class EventSystem;

    // To be called at the start of each game frame.
    void update() noexcept {
        m_key_up.clear();
        m_key_down.clear();
    }

    void set_key_up(ScanCode code) noexcept {
        m_key_up.insert(code);
        m_key.erase(code);
    }

    void set_key_down(ScanCode code) noexcept {
        m_key_down.insert(code);
        m_key.insert(code);
    }

    void set_mouse_up(MouseCode code) noexcept {
        m_mouse_up.insert(code);
        m_mouse.erase(code);
    }

    void set_mouse_down(MouseCode code) noexcept {
        m_mouse_down.insert(code);
        m_mouse.insert(code);
    }

    void set_mouse_position(const Point &position) noexcept {
        m_mouse_position = position;
    }

private:

    std::unordered_set<ScanCode> m_key;

    std::unordered_set<ScanCode> m_key_up;

    std::unordered_set<ScanCode> m_key_down;

    std::unordered_set<MouseCode> m_mouse;

    std::unordered_set<MouseCode> m_mouse_up;

    std::unordered_set<MouseCode> m_mouse_down;

    Point m_mouse_position;
};
