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

    inline Window(const Size &size, const std::string &title) :
        m_render_window(sf::VideoMode(sf::Vector2u(size.width(), size.height())), title) { }

    inline bool is_open() const {
        return m_render_window.isOpen();
    }

    inline void close() {
        m_render_window.close();
    }

    inline void clear(const Color &color) {
        const auto [r, g, b, a] = color;
        m_render_window.clear(sf::Color(r, g, b, a));
    }

    inline void display() {
        m_render_window.display();
    }

    std::optional<AnyEvent> next_event();

private:
friend class LabelNode;
friend class ShapeNode;
friend class SpriteNode;

    inline sf::RenderWindow &render_window() {
        return m_render_window;
    }

private:

    sf::RenderWindow m_render_window;
};
