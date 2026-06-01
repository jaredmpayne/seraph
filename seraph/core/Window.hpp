#pragma once

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/event/AnyEvent.hpp>

class Window {

public:

    Window(const Size &size, const std::string &title = "") :
        m_render_window(sf::VideoMode(sf::Vector2u(size.width(), size.height())), title) { }

    Window(Window &&) noexcept = default;

    Window &operator=(Window &&) noexcept = default;

    Window(const Window &) noexcept = delete;

    Window &operator=(const Window &) noexcept = delete;

    bool is_open() const {
        return m_render_window.isOpen();
    }

    void close() {
        m_render_window.close();
    }

    virtual void on_gain_focus() { };

    virtual void on_lose_focus() { };

    virtual void on_resize(const Size &) { };

private:
friend class Game;

    void clear(const Color &color) {
        const auto [r, g, b, a] = color;
        m_render_window.clear(sf::Color(r, g, b, a));
    }

    void display() {
        m_render_window.display();
    }

private:
friend class EventSystem;

    std::optional<AnyEvent> next_event();

private:
friend class LabelNode;
friend class ShapeNode;
friend class SpriteNode;

    sf::RenderWindow &render_window() {
        return m_render_window;
    }

private:

    sf::RenderWindow m_render_window;
};
