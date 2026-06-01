#pragma once

#include <SFML/Graphics.hpp>

#include <seraph/core/Color.hpp>
#include <seraph/core/Point.hpp>
#include <seraph/core/Rectangle.hpp>
#include <seraph/core/Vector.hpp>
#include <seraph/core/Window.hpp>
#include <seraph/node/Node.hpp>

/// A node for drawing simple regular polygons.
class ShapeNode : public Node {

public:

    ShapeNode(float radius, unsigned int sides_count) :
        m_shape(radius, sides_count) {

        m_shape.setOrigin(sf::Vector2f(radius, radius));
        const auto [fr, fg, fb, fa] = m_shape.getFillColor();
        const auto [sr, sg, sb, sa] = m_shape.getOutlineColor();
        m_fill_color = Color(fr, fg, fb, fa);
        m_stroke_color = Color(sr, sg, sb, sa);
    }

    constexpr float radius() const {
        return m_shape.getRadius();
    }

    void set_radius(float radius) {
        m_shape.setRadius(radius);
        m_shape.setOrigin(sf::Vector2f(radius, radius));
    }

    constexpr unsigned int sides_count() const {
        return m_shape.getPointCount();
    }

    void set_sides_count(unsigned int sides_count) {
        m_shape.setPointCount(sides_count);
    }

    constexpr const Color &fill_color() const noexcept {
        return m_fill_color;
    }

    void set_fill_color(const Color &fill_color) {
        m_fill_color = fill_color;
        const auto [r, g, b, a] = fill_color;
        m_shape.setFillColor(sf::Color(r, g, b, a));
    }

    constexpr float stroke() const {
        return m_shape.getOutlineThickness();
    }

    void set_stroke(float stroke) {
        m_shape.setOutlineThickness(stroke);
    }

    constexpr const Color &stroke_color() const noexcept {
        return m_stroke_color;
    }

    void set_stroke_color(const Color &stroke_color) {
        m_stroke_color = stroke_color;
        const auto [r, g, b, a] = stroke_color;
        m_shape.setOutlineColor(sf::Color(r, g, b, a));
    }

    virtual Rectangle frame() const override {
        const auto bounds = m_shape.getGlobalBounds();
        const auto [x, y] = bounds.position;
        const auto [width, height] = bounds.size;
        return Rectangle(x, y, width, height);
    }

    virtual void draw(Window &window) override {
        const auto [x, y] = absolute_position();
        const auto rotation = absolute_rotation();
        const auto [dx, dy] = absolute_scale();
        m_shape.setPosition(sf::Vector2f(x, y));
        m_shape.setRotation(sf::radians(rotation));
        m_shape.setScale(sf::Vector2f(dx, dy));
        window.render_window().draw(m_shape);
    }

private:

    sf::CircleShape m_shape;

    Color m_fill_color;

    Color m_stroke_color;
};
