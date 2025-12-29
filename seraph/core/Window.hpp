#pragma once

#include <optional>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Size.hpp>
#include <seraph/event/AnyEvent.hpp>

class Node;
class LabelNode;
class ShapeNode;
class SpriteNode;

class Window {

public:

    Window(const Size &size, const std::string &title) :
        m_render_window(sf::VideoMode(sf::Vector2u(size.width(), size.height())), title) { }

    bool is_open() const {
        return m_render_window.isOpen();
    }

    void close() {
        m_render_window.close();
    }

    void clear(const Color &color) {
        const auto [r, g, b, a] = color;
        m_render_window.clear(sf::Color(r, g, b, a));
    }

    void display() {
        m_render_window.display();
    }

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
