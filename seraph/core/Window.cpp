#include <seraph/core/Window.hpp>

#include <optional>
#include <string>

#include <SFML/Window.hpp>

#include <seraph/core/Point.hpp>
#include <seraph/core/Size.hpp>
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
            return AnyEvent(WindowClosedEvent());
        }
        if (event->is<sf::Event::FocusGained>()) {
            return AnyEvent(FocusGainedEvent());
        }
        if (event->is<sf::Event::FocusLost>()) {
            return AnyEvent(FocusLostEvent());
        }
        if (const auto key_event = event->getIf<sf::Event::KeyPressed>()) {
            return AnyEvent(KeyPressedEvent(KeyCode(key_event->code)));
        }
        if (const auto key_event = event->getIf<sf::Event::KeyReleased>()) {
            return AnyEvent(KeyReleasedEvent(KeyCode(key_event->code)));
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseButtonPressed>()) {
            const auto [x, y] = mouse_event->position;
            return AnyEvent(MousePressedEvent(MouseCode(mouse_event->button), Point(x, y)));
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseButtonReleased>()) {
            const auto [x, y] = mouse_event->position;
            return AnyEvent(MouseReleasedEvent(MouseCode(mouse_event->button), Point(x, y)));
        }
        if (const auto mouse_event = event->getIf<sf::Event::MouseMoved>()) {
            const auto [x, y] = mouse_event->position;
            return AnyEvent(MouseMovedEvent(Point(x, y)));
        }
        if (const auto window_event = event->getIf<sf::Event::Resized>()) {
            const auto [width, height] = window_event->size;
            return AnyEvent(WindowResizedEvent(Size(width, height)));
        }
    }
    return std::nullopt;
}
