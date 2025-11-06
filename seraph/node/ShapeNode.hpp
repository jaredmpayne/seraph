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

    ShapeNode(float radius, unsigned int sides_count);

    virtual ~ShapeNode() override = default;

    constexpr float radius() const {
        return m_shape.getRadius();
    }

    inline void set_radius(float radius) {
        m_shape.setRadius(radius);
        m_shape.setOrigin(sf::Vector2f(radius, radius));
    }

    constexpr unsigned int sides_count() const {
        return m_shape.getPointCount();
    }

    inline void set_sides_count(unsigned int sides_count) {
        m_shape.setPointCount(sides_count);
    }

    constexpr const Color &fill_color() const noexcept {
        return m_fill_color;
    }

    void set_fill_color(const Color &fill_color) {
        m_fill_color = fill_color;
        m_shape.setFillColor(sf::Color(fill_color.r(), fill_color.g(), fill_color.b(), fill_color.a()));
    }

    constexpr float stroke() const {
        return m_shape.getOutlineThickness();
    }

    inline void set_stroke(float stroke) {
        m_shape.setOutlineThickness(stroke);
    }

    constexpr const Color &stroke_color() const noexcept {
        return m_stroke_color;
    }

    inline void set_stroke_color(const Color &stroke_color) {
        m_stroke_color = stroke_color;
        const auto [r, g, b, a] = stroke_color;
        m_shape.setOutlineColor(sf::Color(r, g, b, a));
    }

    virtual Rectangle frame() const override;

    virtual void draw(Window &window) override;

private:

    Color m_fill_color;

    Color m_stroke_color;

    sf::CircleShape m_shape;
};
