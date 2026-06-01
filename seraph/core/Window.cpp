#include <seraph/core/Window.hpp>

#include <optional>
#include <string>

#include <SFML/Window.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/event/AnyEvent.hpp>
#include <seraph/event/FocusGainedEvent.hpp>
#include <seraph/event/FocusLostEvent.hpp>
#include <seraph/event/KeyPressedEvent.hpp>
#include <seraph/event/KeyReleasedEvent.hpp>
#include <seraph/event/MouseMovedEvent.hpp>
#include <seraph/event/MousePressedEvent.hpp>
#include <seraph/event/MouseReleasedEvent.hpp>
#include <seraph/event/WindowClosedEvent.hpp>
#include <seraph/event/WindowResizedEvent.hpp>

std::optional<AnyEvent> Window::next_event() {
    if (const auto event = m_render_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            return WindowClosedEvent().erased();
        }
        if (event->is<sf::Event::FocusGained>()) {
            return FocusGainedEvent().erased();
        }
        if (event->is<sf::Event::FocusLost>()) {
            return FocusLostEvent().erased();
        }
        if (const auto key_event = event->getIf<sf::Event::KeyPressed>()) {
            const auto value = int(key_event->code);
            return KeyPressedEvent(*KeyCode::from_value(value)).erased();
        }
        if (const auto key_event = event->getIf<sf::Event::KeyReleased>()) {
            const auto value = int(key_event->code);
            return KeyReleasedEvent(*KeyCode::from_value(value)).erased();
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>()) {
            const auto value = int(mouse_event->button);
            const auto [x, y] = mouse_event->position;
            return MousePressedEvent(*MouseCode::from_value(value), Point(x, y)).erased();
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseButtonReleased>()) {
            const auto value = int(mouse_event->button);
            const auto [x, y] = mouse_event->position;
            return MouseReleasedEvent(*MouseCode::from_value(value), Point(x, y)).erased();
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseMoved>()) {
            const auto [x, y] = mouse_event->position;
            return MouseMovedEvent(Point(x, y)).erased();
        }
        if (const auto window_event = event->getIf<sf::Event::Resized>()) {
            const auto [width, height] = window_event->size;
            return WindowResizedEvent(Size(width, height)).erased();
        }
    }
    return std::nullopt;
}
