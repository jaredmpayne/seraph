#pragma once

#include <string>

#include <SFML/Window/Keyboard.hpp>

#include <seraph/core/Input.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/core/VisitSet.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/event/FocusGainedEvent.hpp>
#include <seraph/event/FocusLostEvent.hpp>
#include <seraph/event/KeyPressedEvent.hpp>
#include <seraph/event/KeyReleasedEvent.hpp>
#include <seraph/event/MouseMovedEvent.hpp>
#include <seraph/event/MousePressedEvent.hpp>
#include <seraph/event/MouseReleasedEvent.hpp>
#include <seraph/event/WindowClosedEvent.hpp>
#include <seraph/event/WindowResizedEvent.hpp>

class EventSystem {

public:

    EventSystem(Input &input, Window &window) noexcept :
        m_input(input),
        m_window(window) { }

    void update() noexcept {
        m_input.update();
        while (const auto event = m_window.next_event()) {
            std::visit(
                VisitSet {
                    [&](const FocusGainedEvent &event) {
                        m_window.on_gain_focus();
                    },
                    [&](const FocusLostEvent &event) {
                        m_window.on_lose_focus();
                    },
                    [&](const KeyPressedEvent &event) {
                        m_input.set_key_down(event.key_code());

                        // SFML provides info regarding Ctrl/Alt/Shift/System
                        // in their events, but it doesn't discern between
                        // left and right so we need to do this instead.
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                            m_input.set_key_down(KeyCode::left_ctrl());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)) {
                            m_input.set_key_down(KeyCode::left_alt());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
                            m_input.set_key_down(KeyCode::left_shift());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LSystem)) {
                            m_input.set_key_down(KeyCode::left_system());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) {
                            m_input.set_key_down(KeyCode::right_ctrl());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt)) {
                            m_input.set_key_down(KeyCode::right_alt());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
                            m_input.set_key_down(KeyCode::right_shift());
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RSystem)) {
                            m_input.set_key_down(KeyCode::right_system());
                        }
                    },
                    [&](const KeyReleasedEvent &event) {
                        m_input.set_key_up(event.key_code());
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                            m_input.set_key_up(KeyCode::left_ctrl());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)) {
                            m_input.set_key_up(KeyCode::left_alt());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
                            m_input.set_key_up(KeyCode::left_shift());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LSystem)) {
                            m_input.set_key_up(KeyCode::left_system());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) {
                            m_input.set_key_up(KeyCode::right_ctrl());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RAlt)) {
                            m_input.set_key_up(KeyCode::right_alt());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
                            m_input.set_key_up(KeyCode::right_shift());
                        }
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RSystem)) {
                            m_input.set_key_up(KeyCode::right_system());
                        }
                    },
                    [&](const MouseMovedEvent &event) {
                        m_input.set_mouse_position(event.position());
                    },
                    [&](const MousePressedEvent &event) {
                        m_input.set_mouse_down(event.mouse_code());
                    },
                    [&](const MouseReleasedEvent &event) {
                        m_input.set_mouse_up(event.mouse_code());
                    },
                    [&](const WindowClosedEvent &event) {
                        m_window.close();
                    },
                    [&](const WindowResizedEvent &event) {
                        m_window.on_resize(event.size());
                    },

                    // TODO: Implement the remaining event types handled by SFML.
                    [](const auto &event) { }
                },
                *event
            );
        }
    }

private:

    Input &m_input;

    Window &m_window;
};
